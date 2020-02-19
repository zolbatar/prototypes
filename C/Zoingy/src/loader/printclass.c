#include <stdlib.h>
#include <string.h>
#include <stdio.h> 
#include "classfile_structs.h"
#include "classfile_consts.h"
#include "getblock.h"

void print_code(unsigned int attribute_code_length, u1 *code)
{
    unsigned int code_pc = 0;
    while (code_pc < attribute_code_length)
    {
        short opcode = code[code_pc++];
        printf("\t\t[%.8i] [%.2hx]\t\t", code_pc, opcode);
        switch (opcode)
        {
            case 0x12:
            {
                printf("ldc %x", get_u1(code, &code_pc));
                break;
            }
            case 0x2a:
            {
                printf("aload_0");
                break;
            }
            case 0xb1:
            {
                printf("return");
                break;
            }
            case 0xb2:
            {
                printf("getstatic %x", get_u2(code, &code_pc));
                break;
            }
            case 0xb6:
            {
                printf("invokevirtual %x", get_u2(code, &code_pc));
                break;
            }
            case 0xb7:
            {
                printf("invokespecial %x", get_u2(code, &code_pc));
                break;
            }
            default:
            {
                printf("[%i] %hx", code_pc, opcode);
                break;
            }
        }
        printf("\n");
    }   
}

void print_class_header(class_file *class)
{
    /* Summary */
    printf("Summary\n-------\n");
    printf("Version: %X.%X\n", class->minor_version, class->major_version);
    printf("Access Flags: ACC_PUBLIC=%i ACC_FINAL=%i ACC_SUPER=%i ACC_INTERFACE=%i ACC_ABSTRACT=%i\n", (class->access_flags & ACC_PUBLIC) > 0, (class->access_flags & ACC_FINAL) > 0, 
        (class->access_flags & ACC_SUPER) > 0, (class->access_flags & ACC_INTERFACE) > 0, (class->access_flags & ACC_ABSTRACT) > 0);
    printf("This Class: %i\nSuper Class: %i\n", class->this_class, class->super_class);

    /* Constant Pool */
    printf("\nConstant Pool\n-------------\n");
    printf("Constant pool count: %i\n", class->constant_pool_count);
    unsigned int constant;
    for (constant = 0; constant < class->constant_pool_count - 1; constant++)
    {
        cp_info *info = ((cp_info *)class->constant_pool[constant]);
        switch (info->tag)
        {
            case CONSTANT_Methodref:
            {
                CONSTANT_Methodref_info *obj = ((CONSTANT_Methodref_info *)class->constant_pool[constant]);
                printf("[%i] Methodref:%i/%i\n", constant + 1, obj->class_index, obj->name_and_type_index);
                break;
            }
            case CONSTANT_Fieldref:
            {
                CONSTANT_Fieldref_info *obj = ((CONSTANT_Fieldref_info *)class->constant_pool[constant]);
                printf("[%i] Fieldref:%i/%i\n", constant + 1, obj->class_index, obj->name_and_type_index);
                break;
            }
            case CONSTANT_String:
            {
                CONSTANT_String_info *obj = ((CONSTANT_String_info *)class->constant_pool[constant]);
                printf("[%i] String:%i\n", constant + 1, obj->string_index);
                break;
            }
            case CONSTANT_NameAndType:
            {
                CONSTANT_NameAndType_info *obj = ((CONSTANT_NameAndType_info *)class->constant_pool[constant]);
                printf("[%i] NameAndType:%i/%i\n", constant + 1, obj->name_index, obj->descriptor_index);
                break;
            }
            case CONSTANT_Class:
            {
                CONSTANT_Class_info *obj = ((CONSTANT_Class_info *)class->constant_pool[constant]);
                printf("[%i] Class:%i\n", constant + 1, obj->name_index);
                break;
            }
            case CONSTANT_Utf8:
            {
                CONSTANT_Utf8_info *obj = ((CONSTANT_Utf8_info *)class->constant_pool[constant]);
                printf("[%i] UTF8:'%s' Length:%i\n", constant + 1, obj->bytes, obj->length);
                break;
            }
        }
    }
    
    /* Interfaces */
    printf("\nInterfaces\n---------\n");
    printf("Interfaces Count: %i\n", class->interfaces_count);
    unsigned int interface;
    for (interface = 0; interface < class->interfaces_count; interface++)
    {
        printf("[%i] = %i", interface, class->interfaces[interface]);
    }
    
    /* Fields */
    printf("\nFields\n------\n");
    printf("Fields Count: %i\n", class->fields_count);
    unsigned int field;
    for (field = 0; field < class->fields_count; field++)
    {
    }
    
    /* Methods */
    printf("\nMethods\n-------\n");
    printf("Methods Count: %i\n", class->methods_count);
    unsigned int method;
    for (method = 0; method < class->methods_count; method++)
    {
        method_info *obj = ((method_info *)class->methods[method]);
        printf("[%i] AccessFlags:%i NameIndex:%i DescriptorIndex:%i AttributesCount:%i\n", method, obj->access_flags, obj->name_index, obj->descriptor_index, obj->attributes_count);

        unsigned int method_attributes;
        for (method_attributes = 0; method_attributes < obj->attributes_count; method_attributes++)
        {
            attribute_info *attr_obj = ((attribute_info *)obj->attributes[method]);
            switch (attr_obj->type)
            {
                case METHOD_ATTR_OTHER:
                {
                    printf("  -> [%i] NameIndex:%i Length:%i [Other]\n", method_attributes, attr_obj->attribute_name_index, attr_obj->attribute_length);
                    break;
                }
                case METHOD_ATTR_CODE:
                {
                    code_attribute *attr_obj = ((code_attribute *)obj->attributes[method]);
                    printf("  -> [%i] NameIndex:%i Length:%i[Code]\n", method_attributes, attr_obj->attribute_name_index, attr_obj->attribute_length);
                    printf("    --> MaxStack:%i MaxLocals:%i CodeLength:%i ExceptionTableLength:%i AttributesCount:%i\n", 
                        attr_obj->max_stack, attr_obj->max_locals, attr_obj->code_length, attr_obj->exception_table_length, attr_obj->attributes_count);

                    unsigned int exception_item;
                    for (exception_item = 0; exception_item < attr_obj->exception_table_length; exception_item++)
                    {
                        code_exception *exception = ((code_exception *)attr_obj->exception_table[exception_item]);
                        printf("    --> Exception [%i] StartPC:%i EndPC:%i HandlerPC:%i CatchType:%i\n", exception_item, exception->start_pc, exception->end_pc, exception->handler_pc, exception->catch_type);
                    } 

                    /* Attributes */
                    unsigned int code_attribute_item;
                    for (code_attribute_item = 0; code_attribute_item < attr_obj->attributes_count; code_attribute_item++)
                    {
                        attribute_info *code_attribute = ((attribute_info *)attr_obj->attributes[code_attribute_item]);
                        printf("    --> Attribute [%i] NameIndex:%i Length:%i Value:'%s'\n", code_attribute_item, code_attribute->attribute_name_index, code_attribute->attribute_length, (char *)code_attribute->info);
                    }
                    
                    /* Dump code */
                    print_code(attr_obj->code_length, attr_obj->code);

                    break;
                }
            }
        }
    }
}
