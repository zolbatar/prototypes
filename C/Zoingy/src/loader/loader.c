#include <stdlib.h>
#include <string.h>
#include <stdio.h> 
#include "classfile_structs.h"
#include "classfile_consts.h"
#include "getblock.h"

/* Actual decoding logic */
int decode_class_header(unsigned char *header, unsigned int length, class_file *class)
{
    unsigned int pos = 0;

    /* Verify magic */
    class->magic = get_u4(header, &pos);
    if (class->magic != 0xCAFEBABE)
    {
        printf("Magic not found.\n");
        return false;
    }
    
    /* Version */
    class->minor_version = get_u2(header, &pos);
    class->major_version = get_u2(header, &pos);
    
    /* Constant Pool */
    class->constant_pool_count = get_u2(header, &pos);
    class->constant_pool = malloc(class->constant_pool_count * sizeof(void *));
    unsigned int constant;
    for (constant = 0; constant < class->constant_pool_count - 1; constant++)
    {
        unsigned char tag = get_u1(header, &pos);;
        switch (tag)
        {
            case CONSTANT_Methodref:
            {
                class->constant_pool[constant] = malloc(sizeof(CONSTANT_Methodref_info));
                CONSTANT_Methodref_info *obj = ((CONSTANT_Methodref_info *)class->constant_pool[constant]);
                obj->tag = tag;
                obj->class_index = get_u2(header, &pos);
                obj->name_and_type_index = get_u2(header, &pos);
                break;
            }
            case CONSTANT_Fieldref:
            {
                class->constant_pool[constant] = malloc(sizeof(CONSTANT_Fieldref_info));
                CONSTANT_Fieldref_info *obj = ((CONSTANT_Fieldref_info *)class->constant_pool[constant]);
                obj->tag = tag;
                obj->class_index = get_u2(header, &pos);
                obj->name_and_type_index = get_u2(header, &pos);
                break;
            }
            case CONSTANT_String:
            {
                class->constant_pool[constant] = malloc(sizeof(CONSTANT_String_info));
                CONSTANT_String_info *obj = ((CONSTANT_String_info *)class->constant_pool[constant]);
                obj->tag = tag;
                obj->string_index = get_u2(header, &pos);
                break;
            }
            case CONSTANT_NameAndType:
            {
                class->constant_pool[constant] = malloc(sizeof(CONSTANT_NameAndType_info));
                CONSTANT_NameAndType_info *obj = ((CONSTANT_NameAndType_info *)class->constant_pool[constant]);
                obj->tag = tag;
                obj->name_index = get_u2(header, &pos);
                obj->descriptor_index = get_u2(header, &pos);
                break;
            }
            case CONSTANT_Class:
            {
                class->constant_pool[constant] = malloc(sizeof(CONSTANT_Class_info));
                CONSTANT_Class_info *obj = ((CONSTANT_Class_info *)class->constant_pool[constant]);
                obj->tag = tag;
                obj->name_index = get_u2(header, &pos);
                break;
            }
            case CONSTANT_Utf8:
            {
                class->constant_pool[constant] = malloc(sizeof(CONSTANT_Utf8_info));
                CONSTANT_Utf8_info *obj = ((CONSTANT_Utf8_info *)class->constant_pool[constant]);
                obj->tag = tag;
                obj->length = get_u2(header, &pos);
                obj->bytes = get_utf8(header, &pos, obj->length);
                break;
            }
            default:
            {
                printf ("Unsupported constant tag %i", tag);
                exit(1);
            }
        }
    }
    
    /* Access flags */
    class->access_flags = get_u2(header, &pos);
    
    /* Class */
    class->this_class = get_u2(header, &pos);
    class->super_class = get_u2(header, &pos);

    /* Interfaces */
    class->interfaces_count = get_u2(header, &pos);
    class->interfaces = malloc(class->interfaces_count * sizeof(u2));
    unsigned int interface;
    for (interface = 0; interface < class->interfaces_count; interface++)
    {
        class->interfaces[interface] = get_u2(header, &pos);
    }

    /* Fields */
    class->fields_count = get_u2(header, &pos);
    unsigned int field;
    for (field = 0; field < class->fields_count; field++)
    {
        printf("Oh dear, fields not implemented yet!");
        exit(1);
    }
    
    /* Methods */
    class->methods_count = get_u2(header, &pos);
    class->methods = malloc(class->methods_count * sizeof(method_info));
    unsigned int method;
    for (method = 0; method < class->methods_count; method++)
    {
        class->methods[method] = malloc(sizeof(method_info));
        method_info *obj = ((method_info *)class->methods[method]);
        obj->access_flags = get_u2(header, &pos);
        obj->name_index = get_u2(header, &pos);
        obj->descriptor_index = get_u2(header, &pos);
        obj->attributes_count = get_u2(header, &pos);
        
        obj->attributes = malloc(obj->attributes_count * sizeof(attribute_info));
        unsigned int method_attributes;
        for (method_attributes = 0; method_attributes < obj->attributes_count; method_attributes++)
        {
            u2 attribute_name_index = get_u2(header, &pos);
            u4 attribute_length = get_u4(header, &pos);

            /* What is it? */
            CONSTANT_Utf8_info *attr_obj_ref = ((CONSTANT_Utf8_info *)class->constant_pool[attribute_name_index - 1]);
            if (strncmp((char *)attr_obj_ref->bytes, "Code", attr_obj_ref->length) == 0)
            {
                obj->attributes[method] = malloc(sizeof(code_attribute));
                code_attribute *attr_obj = ((code_attribute *)obj->attributes[method]);
                attr_obj->type = METHOD_ATTR_CODE;
                attr_obj->attribute_name_index = attribute_name_index;
//              attr_obj->attribute_length;
                attr_obj->max_stack = get_u2(header, &pos);
                attr_obj->max_locals = get_u2(header, &pos);
                attr_obj->code_length = get_u4(header, &pos);
                attr_obj->code = get_data(header, &pos, attr_obj->code_length);

                /* Exceptions */
                attr_obj->exception_table_length = get_u2(header, &pos);
                unsigned int exception_item;
                attr_obj->exception_table = malloc(attr_obj->exception_table_length * sizeof(code_exception));
                for (exception_item = 0; exception_item < attr_obj->exception_table_length; exception_item++)
                {
                    attr_obj->exception_table[exception_item] = malloc(sizeof(code_exception));
                    code_exception *exception = ((code_exception *)attr_obj->exception_table[exception_item]);
                    exception->start_pc = get_u2(header, &pos);
                    exception->end_pc = get_u2(header, &pos);
                    exception->handler_pc = get_u2(header, &pos);
                    exception->catch_type = get_u2(header, &pos);
                } 

                /* Attributes */
                attr_obj->attributes_count = get_u2(header, &pos);
                attr_obj->attributes = malloc(attr_obj->attributes_count * sizeof(attribute_info));
                unsigned int code_attribute_item;
                for (code_attribute_item = 0; code_attribute_item < attr_obj->attributes_count; code_attribute_item++)
                {
                    attr_obj->attributes[code_attribute_item] = malloc(sizeof(attribute_info));
                    attribute_info *code_attribute = ((attribute_info *)attr_obj->attributes[code_attribute_item]);
                    code_attribute->attribute_name_index = get_u2(header, &pos);
                    code_attribute->attribute_length = get_u4(header, &pos);
                    code_attribute->info = get_data(header, &pos, code_attribute->attribute_length);
                }
            }
            else
            {
                obj->attributes[method] = malloc(sizeof(attribute_info));
                attribute_info *attr_obj = ((attribute_info *)obj->attributes[method]);
                attr_obj->type = METHOD_ATTR_OTHER;
                attr_obj->attribute_name_index = attribute_name_index;
//              attr_obj->attribute_length;
                attr_obj->info = get_data(header, &pos, attr_obj->attribute_length);
            }
        }
    }

    return true;
}

void delete_class(class_file *class)
{
    free(class->constant_pool);
}
