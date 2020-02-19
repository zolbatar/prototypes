goog.provide('cljs.core');
goog.require('goog.array');
goog.require('goog.object');
goog.require('goog.string.format');
goog.require('goog.string.StringBuffer');
goog.require('goog.string');
cljs.core._STAR_unchecked_if_STAR_ = false;
/**
* Each runtime environment provides a diffenent way to print output.
* Whatever function *print-fn* is bound to will be passed any
* Strings which should be printed.
*/
cljs.core._STAR_print_fn_STAR_ = (function _STAR_print_fn_STAR_(_){
throw (new Error("No *print-fn* fn set for evaluation environment"));
});
/**
* Internal - do not use!
*/
cljs.core.truth_ = (function truth_(x){
return (x != null && x !== false);
});
/**
* Internal - do not use!
*/
cljs.core.type_satisfies_ = (function type_satisfies_(p,x){
var x__6283 = (((x == null))?null:x);
if((p[goog.typeOf(x__6283)]))
{return true;
} else
{if((p["_"]))
{return true;
} else
{if("\uFDD0'else")
{return false;
} else
{return null;
}
}
}
});
cljs.core.is_proto_ = (function is_proto_(x){
return (x.constructor.prototype === x);
});
/**
* When compiled for a command-line target, whatever
* function *main-fn* is set to will be called with the command-line
* argv as arguments
*/
cljs.core._STAR_main_cli_fn_STAR_ = null;
cljs.core.missing_protocol = (function missing_protocol(proto,obj){
return Error(["No protocol method ",proto," defined for type ",goog.typeOf(obj),": ",obj].join(""));
});
/**
* Returns a javascript array, cloned from the passed in array
*/
cljs.core.aclone = (function aclone(array_like){
return array_like.slice();
});
/**
* Creates a new javascript array.
* @param {...*} var_args
*/
cljs.core.array = (function array(var_args){
return Array.prototype.slice.call(arguments);
});
cljs.core.make_array = (function() {
var make_array = null;
var make_array__1 = (function (size){
return (new Array(size));
});
var make_array__2 = (function (type,size){
return make_array.call(null,size);
});
make_array = function(type,size){
switch(arguments.length){
case 1:
return make_array__1.call(this,type);
case 2:
return make_array__2.call(this,type,size);
}
throw('Invalid arity: ' + arguments.length);
};
make_array.cljs$lang$arity$1 = make_array__1;
make_array.cljs$lang$arity$2 = make_array__2;
return make_array;
})()
;
/**
* Returns the value at the index.
* @param {...*} var_args
*/
cljs.core.aget = (function() {
var aget = null;
var aget__2 = (function (array,i){
return (array[i]);
});
var aget__3 = (function() { 
var G__6284__delegate = function (array,i,idxs){
return cljs.core.apply.call(null,aget,aget.call(null,array,i),idxs);
};
var G__6284 = function (array,i,var_args){
var idxs = null;
if (goog.isDef(var_args)) {
  idxs = cljs.core.array_seq(Array.prototype.slice.call(arguments, 2),0);
} 
return G__6284__delegate.call(this, array, i, idxs);
};
G__6284.cljs$lang$maxFixedArity = 2;
G__6284.cljs$lang$applyTo = (function (arglist__6285){
var array = cljs.core.first(arglist__6285);
var i = cljs.core.first(cljs.core.next(arglist__6285));
var idxs = cljs.core.rest(cljs.core.next(arglist__6285));
return G__6284__delegate(array, i, idxs);
});
G__6284.cljs$lang$arity$variadic = G__6284__delegate;
return G__6284;
})()
;
aget = function(array,i,var_args){
var idxs = var_args;
switch(arguments.length){
case 2:
return aget__2.call(this,array,i);
default:
return aget__3.cljs$lang$arity$variadic(array,i, cljs.core.array_seq(arguments, 2));
}
throw('Invalid arity: ' + arguments.length);
};
aget.cljs$lang$maxFixedArity = 2;
aget.cljs$lang$applyTo = aget__3.cljs$lang$applyTo;
aget.cljs$lang$arity$2 = aget__2;
aget.cljs$lang$arity$variadic = aget__3.cljs$lang$arity$variadic;
return aget;
})()
;
/**
* Sets the value at the index.
*/
cljs.core.aset = (function aset(array,i,val){
return (array[i] = val);
});
/**
* Returns the length of the array. Works on arrays of all types.
*/
cljs.core.alength = (function alength(array){
return array.length;
});
cljs.core.into_array = (function() {
var into_array = null;
var into_array__1 = (function (aseq){
return into_array.call(null,null,aseq);
});
var into_array__2 = (function (type,aseq){
return cljs.core.reduce.call(null,(function (a,x){
a.push(x);
return a;
}),[],aseq);
});
into_array = function(type,aseq){
switch(arguments.length){
case 1:
return into_array__1.call(this,type);
case 2:
return into_array__2.call(this,type,aseq);
}
throw('Invalid arity: ' + arguments.length);
};
into_array.cljs$lang$arity$1 = into_array__1;
into_array.cljs$lang$arity$2 = into_array__2;
return into_array;
})()
;
cljs.core.IFn = {};
cljs.core._invoke = (function() {
var _invoke = null;
var _invoke__1 = (function (this$){
if((function (){var and__3822__auto____6370 = this$;
if(and__3822__auto____6370)
{return this$.cljs$core$IFn$_invoke$arity$1;
} else
{return and__3822__auto____6370;
}
})())
{return this$.cljs$core$IFn$_invoke$arity$1(this$);
} else
{var x__2391__auto____6371 = (((this$ == null))?null:this$);
return (function (){var or__3824__auto____6372 = (cljs.core._invoke[goog.typeOf(x__2391__auto____6371)]);
if(or__3824__auto____6372)
{return or__3824__auto____6372;
} else
{var or__3824__auto____6373 = (cljs.core._invoke["_"]);
if(or__3824__auto____6373)
{return or__3824__auto____6373;
} else
{throw cljs.core.missing_protocol.call(null,"IFn.-invoke",this$);
}
}
})().call(null,this$);
}
});
var _invoke__2 = (function (this$,a){
if((function (){var and__3822__auto____6374 = this$;
if(and__3822__auto____6374)
{return this$.cljs$core$IFn$_invoke$arity$2;
} else
{return and__3822__auto____6374;
}
})())
{return this$.cljs$core$IFn$_invoke$arity$2(this$,a);
} else
{var x__2391__auto____6375 = (((this$ == null))?null:this$);
return (function (){var or__3824__auto____6376 = (cljs.core._invoke[goog.typeOf(x__2391__auto____6375)]);
if(or__3824__auto____6376)
{return or__3824__auto____6376;
} else
{var or__3824__auto____6377 = (cljs.core._invoke["_"]);
if(or__3824__auto____6377)
{return or__3824__auto____6377;
} else
{throw cljs.core.missing_protocol.call(null,"IFn.-invoke",this$);
}
}
})().call(null,this$,a);
}
});
var _invoke__3 = (function (this$,a,b){
if((function (){var and__3822__auto____6378 = this$;
if(and__3822__auto____6378)
{return this$.cljs$core$IFn$_invoke$arity$3;
} else
{return and__3822__auto____6378;
}
})())
{return this$.cljs$core$IFn$_invoke$arity$3(this$,a,b);
} else
{var x__2391__auto____6379 = (((this$ == null))?null:this$);
return (function (){var or__3824__auto____6380 = (cljs.core._invoke[goog.typeOf(x__2391__auto____6379)]);
if(or__3824__auto____6380)
{return or__3824__auto____6380;
} else
{var or__3824__auto____6381 = (cljs.core._invoke["_"]);
if(or__3824__auto____6381)
{return or__3824__auto____6381;
} else
{throw cljs.core.missing_protocol.call(null,"IFn.-invoke",this$);
}
}
})().call(null,this$,a,b);
}
});
var _invoke__4 = (function (this$,a,b,c){
if((function (){var and__3822__auto____6382 = this$;
if(and__3822__auto____6382)
{return this$.cljs$core$IFn$_invoke$arity$4;
} else
{return and__3822__auto____6382;
}
})())
{return this$.cljs$core$IFn$_invoke$arity$4(this$,a,b,c);
} else
{var x__2391__auto____6383 = (((this$ == null))?null:this$);
return (function (){var or__3824__auto____6384 = (cljs.core._invoke[goog.typeOf(x__2391__auto____6383)]);
if(or__3824__auto____6384)
{return or__3824__auto____6384;
} else
{var or__3824__auto____6385 = (cljs.core._invoke["_"]);
if(or__3824__auto____6385)
{return or__3824__auto____6385;
} else
{throw cljs.core.missing_protocol.call(null,"IFn.-invoke",this$);
}
}
})().call(null,this$,a,b,c);
}
});
var _invoke__5 = (function (this$,a,b,c,d){
if((function (){var and__3822__auto____6386 = this$;
if(and__3822__auto____6386)
{return this$.cljs$core$IFn$_invoke$arity$5;
} else
{return and__3822__auto____6386;
}
})())
{return this$.cljs$core$IFn$_invoke$arity$5(this$,a,b,c,d);
} else
{var x__2391__auto____6387 = (((this$ == null))?null:this$);
return (function (){var or__3824__auto____6388 = (cljs.core._invoke[goog.typeOf(x__2391__auto____6387)]);
if(or__3824__auto____6388)
{return or__3824__auto____6388;
} else
{var or__3824__auto____6389 = (cljs.core._invoke["_"]);
if(or__3824__auto____6389)
{return or__3824__auto____6389;
} else
{throw cljs.core.missing_protocol.call(null,"IFn.-invoke",this$);
}
}
})().call(null,this$,a,b,c,d);
}
});
var _invoke__6 = (function (this$,a,b,c,d,e){
if((function (){var and__3822__auto____6390 = this$;
if(and__3822__auto____6390)
{return this$.cljs$core$IFn$_invoke$arity$6;
} else
{return and__3822__auto____6390;
}
})())
{return this$.cljs$core$IFn$_invoke$arity$6(this$,a,b,c,d,e);
} else
{var x__2391__auto____6391 = (((this$ == null))?null:this$);
return (function (){var or__3824__auto____6392 = (cljs.core._invoke[goog.typeOf(x__2391__auto____6391)]);
if(or__3824__auto____6392)
{return or__3824__auto____6392;
} else
{var or__3824__auto____6393 = (cljs.core._invoke["_"]);
if(or__3824__auto____6393)
{return or__3824__auto____6393;
} else
{throw cljs.core.missing_protocol.call(null,"IFn.-invoke",this$);
}
}
})().call(null,this$,a,b,c,d,e);
}
});
var _invoke__7 = (function (this$,a,b,c,d,e,f){
if((function (){var and__3822__auto____6394 = this$;
if(and__3822__auto____6394)
{return this$.cljs$core$IFn$_invoke$arity$7;
} else
{return and__3822__auto____6394;
}
})())
{return this$.cljs$core$IFn$_invoke$arity$7(this$,a,b,c,d,e,f);
} else
{var x__2391__auto____6395 = (((this$ == null))?null:this$);
return (function (){var or__3824__auto____6396 = (cljs.core._invoke[goog.typeOf(x__2391__auto____6395)]);
if(or__3824__auto____6396)
{return or__3824__auto____6396;
} else
{var or__3824__auto____6397 = (cljs.core._invoke["_"]);
if(or__3824__auto____6397)
{return or__3824__auto____6397;
} else
{throw cljs.core.missing_protocol.call(null,"IFn.-invoke",this$);
}
}
})().call(null,this$,a,b,c,d,e,f);
}
});
var _invoke__8 = (function (this$,a,b,c,d,e,f,g){
if((function (){var and__3822__auto____6398 = this$;
if(and__3822__auto____6398)
{return this$.cljs$core$IFn$_invoke$arity$8;
} else
{return and__3822__auto____6398;
}
})())
{return this$.cljs$core$IFn$_invoke$arity$8(this$,a,b,c,d,e,f,g);
} else
{var x__2391__auto____6399 = (((this$ == null))?null:this$);
return (function (){var or__3824__auto____6400 = (cljs.core._invoke[goog.typeOf(x__2391__auto____6399)]);
if(or__3824__auto____6400)
{return or__3824__auto____6400;
} else
{var or__3824__auto____6401 = (cljs.core._invoke["_"]);
if(or__3824__auto____6401)
{return or__3824__auto____6401;
} else
{throw cljs.core.missing_protocol.call(null,"IFn.-invoke",this$);
}
}
})().call(null,this$,a,b,c,d,e,f,g);
}
});
var _invoke__9 = (function (this$,a,b,c,d,e,f,g,h){
if((function (){var and__3822__auto____6402 = this$;
if(and__3822__auto____6402)
{return this$.cljs$core$IFn$_invoke$arity$9;
} else
{return and__3822__auto____6402;
}
})())
{return this$.cljs$core$IFn$_invoke$arity$9(this$,a,b,c,d,e,f,g,h);
} else
{var x__2391__auto____6403 = (((this$ == null))?null:this$);
return (function (){var or__3824__auto____6404 = (cljs.core._invoke[goog.typeOf(x__2391__auto____6403)]);
if(or__3824__auto____6404)
{return or__3824__auto____6404;
} else
{var or__3824__auto____6405 = (cljs.core._invoke["_"]);
if(or__3824__auto____6405)
{return or__3824__auto____6405;
} else
{throw cljs.core.missing_protocol.call(null,"IFn.-invoke",this$);
}
}
})().call(null,this$,a,b,c,d,e,f,g,h);
}
});
var _invoke__10 = (function (this$,a,b,c,d,e,f,g,h,i){
if((function (){var and__3822__auto____6406 = this$;
if(and__3822__auto____6406)
{return this$.cljs$core$IFn$_invoke$arity$10;
} else
{return and__3822__auto____6406;
}
})())
{return this$.cljs$core$IFn$_invoke$arity$10(this$,a,b,c,d,e,f,g,h,i);
} else
{var x__2391__auto____6407 = (((this$ == null))?null:this$);
return (function (){var or__3824__auto____6408 = (cljs.core._invoke[goog.typeOf(x__2391__auto____6407)]);
if(or__3824__auto____6408)
{return or__3824__auto____6408;
} else
{var or__3824__auto____6409 = (cljs.core._invoke["_"]);
if(or__3824__auto____6409)
{return or__3824__auto____6409;
} else
{throw cljs.core.missing_protocol.call(null,"IFn.-invoke",this$);
}
}
})().call(null,this$,a,b,c,d,e,f,g,h,i);
}
});
var _invoke__11 = (function (this$,a,b,c,d,e,f,g,h,i,j){
if((function (){var and__3822__auto____6410 = this$;
if(and__3822__auto____6410)
{return this$.cljs$core$IFn$_invoke$arity$11;
} else
{return and__3822__auto____6410;
}
})())
{return this$.cljs$core$IFn$_invoke$arity$11(this$,a,b,c,d,e,f,g,h,i,j);
} else
{var x__2391__auto____6411 = (((this$ == null))?null:this$);
return (function (){var or__3824__auto____6412 = (cljs.core._invoke[goog.typeOf(x__2391__auto____6411)]);
if(or__3824__auto____6412)
{return or__3824__auto____6412;
} else
{var or__3824__auto____6413 = (cljs.core._invoke["_"]);
if(or__3824__auto____6413)
{return or__3824__auto____6413;
} else
{throw cljs.core.missing_protocol.call(null,"IFn.-invoke",this$);
}
}
})().call(null,this$,a,b,c,d,e,f,g,h,i,j);
}
});
var _invoke__12 = (function (this$,a,b,c,d,e,f,g,h,i,j,k){
if((function (){var and__3822__auto____6414 = this$;
if(and__3822__auto____6414)
{return this$.cljs$core$IFn$_invoke$arity$12;
} else
{return and__3822__auto____6414;
}
})())
{return this$.cljs$core$IFn$_invoke$arity$12(this$,a,b,c,d,e,f,g,h,i,j,k);
} else
{var x__2391__auto____6415 = (((this$ == null))?null:this$);
return (function (){var or__3824__auto____6416 = (cljs.core._invoke[goog.typeOf(x__2391__auto____6415)]);
if(or__3824__auto____6416)
{return or__3824__auto____6416;
} else
{var or__3824__auto____6417 = (cljs.core._invoke["_"]);
if(or__3824__auto____6417)
{return or__3824__auto____6417;
} else
{throw cljs.core.missing_protocol.call(null,"IFn.-invoke",this$);
}
}
})().call(null,this$,a,b,c,d,e,f,g,h,i,j,k);
}
});
var _invoke__13 = (function (this$,a,b,c,d,e,f,g,h,i,j,k,l){
if((function (){var and__3822__auto____6418 = this$;
if(and__3822__auto____6418)
{return this$.cljs$core$IFn$_invoke$arity$13;
} else
{return and__3822__auto____6418;
}
})())
{return this$.cljs$core$IFn$_invoke$arity$13(this$,a,b,c,d,e,f,g,h,i,j,k,l);
} else
{var x__2391__auto____6419 = (((this$ == null))?null:this$);
return (function (){var or__3824__auto____6420 = (cljs.core._invoke[goog.typeOf(x__2391__auto____6419)]);
if(or__3824__auto____6420)
{return or__3824__auto____6420;
} else
{var or__3824__auto____6421 = (cljs.core._invoke["_"]);
if(or__3824__auto____6421)
{return or__3824__auto____6421;
} else
{throw cljs.core.missing_protocol.call(null,"IFn.-invoke",this$);
}
}
})().call(null,this$,a,b,c,d,e,f,g,h,i,j,k,l);
}
});
var _invoke__14 = (function (this$,a,b,c,d,e,f,g,h,i,j,k,l,m){
if((function (){var and__3822__auto____6422 = this$;
if(and__3822__auto____6422)
{return this$.cljs$core$IFn$_invoke$arity$14;
} else
{return and__3822__auto____6422;
}
})())
{return this$.cljs$core$IFn$_invoke$arity$14(this$,a,b,c,d,e,f,g,h,i,j,k,l,m);
} else
{var x__2391__auto____6423 = (((this$ == null))?null:this$);
return (function (){var or__3824__auto____6424 = (cljs.core._invoke[goog.typeOf(x__2391__auto____6423)]);
if(or__3824__auto____6424)
{return or__3824__auto____6424;
} else
{var or__3824__auto____6425 = (cljs.core._invoke["_"]);
if(or__3824__auto____6425)
{return or__3824__auto____6425;
} else
{throw cljs.core.missing_protocol.call(null,"IFn.-invoke",this$);
}
}
})().call(null,this$,a,b,c,d,e,f,g,h,i,j,k,l,m);
}
});
var _invoke__15 = (function (this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n){
if((function (){var and__3822__auto____6426 = this$;
if(and__3822__auto____6426)
{return this$.cljs$core$IFn$_invoke$arity$15;
} else
{return and__3822__auto____6426;
}
})())
{return this$.cljs$core$IFn$_invoke$arity$15(this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n);
} else
{var x__2391__auto____6427 = (((this$ == null))?null:this$);
return (function (){var or__3824__auto____6428 = (cljs.core._invoke[goog.typeOf(x__2391__auto____6427)]);
if(or__3824__auto____6428)
{return or__3824__auto____6428;
} else
{var or__3824__auto____6429 = (cljs.core._invoke["_"]);
if(or__3824__auto____6429)
{return or__3824__auto____6429;
} else
{throw cljs.core.missing_protocol.call(null,"IFn.-invoke",this$);
}
}
})().call(null,this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n);
}
});
var _invoke__16 = (function (this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o){
if((function (){var and__3822__auto____6430 = this$;
if(and__3822__auto____6430)
{return this$.cljs$core$IFn$_invoke$arity$16;
} else
{return and__3822__auto____6430;
}
})())
{return this$.cljs$core$IFn$_invoke$arity$16(this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o);
} else
{var x__2391__auto____6431 = (((this$ == null))?null:this$);
return (function (){var or__3824__auto____6432 = (cljs.core._invoke[goog.typeOf(x__2391__auto____6431)]);
if(or__3824__auto____6432)
{return or__3824__auto____6432;
} else
{var or__3824__auto____6433 = (cljs.core._invoke["_"]);
if(or__3824__auto____6433)
{return or__3824__auto____6433;
} else
{throw cljs.core.missing_protocol.call(null,"IFn.-invoke",this$);
}
}
})().call(null,this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o);
}
});
var _invoke__17 = (function (this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p){
if((function (){var and__3822__auto____6434 = this$;
if(and__3822__auto____6434)
{return this$.cljs$core$IFn$_invoke$arity$17;
} else
{return and__3822__auto____6434;
}
})())
{return this$.cljs$core$IFn$_invoke$arity$17(this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
} else
{var x__2391__auto____6435 = (((this$ == null))?null:this$);
return (function (){var or__3824__auto____6436 = (cljs.core._invoke[goog.typeOf(x__2391__auto____6435)]);
if(or__3824__auto____6436)
{return or__3824__auto____6436;
} else
{var or__3824__auto____6437 = (cljs.core._invoke["_"]);
if(or__3824__auto____6437)
{return or__3824__auto____6437;
} else
{throw cljs.core.missing_protocol.call(null,"IFn.-invoke",this$);
}
}
})().call(null,this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
}
});
var _invoke__18 = (function (this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q){
if((function (){var and__3822__auto____6438 = this$;
if(and__3822__auto____6438)
{return this$.cljs$core$IFn$_invoke$arity$18;
} else
{return and__3822__auto____6438;
}
})())
{return this$.cljs$core$IFn$_invoke$arity$18(this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q);
} else
{var x__2391__auto____6439 = (((this$ == null))?null:this$);
return (function (){var or__3824__auto____6440 = (cljs.core._invoke[goog.typeOf(x__2391__auto____6439)]);
if(or__3824__auto____6440)
{return or__3824__auto____6440;
} else
{var or__3824__auto____6441 = (cljs.core._invoke["_"]);
if(or__3824__auto____6441)
{return or__3824__auto____6441;
} else
{throw cljs.core.missing_protocol.call(null,"IFn.-invoke",this$);
}
}
})().call(null,this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q);
}
});
var _invoke__19 = (function (this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,s){
if((function (){var and__3822__auto____6442 = this$;
if(and__3822__auto____6442)
{return this$.cljs$core$IFn$_invoke$arity$19;
} else
{return and__3822__auto____6442;
}
})())
{return this$.cljs$core$IFn$_invoke$arity$19(this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,s);
} else
{var x__2391__auto____6443 = (((this$ == null))?null:this$);
return (function (){var or__3824__auto____6444 = (cljs.core._invoke[goog.typeOf(x__2391__auto____6443)]);
if(or__3824__auto____6444)
{return or__3824__auto____6444;
} else
{var or__3824__auto____6445 = (cljs.core._invoke["_"]);
if(or__3824__auto____6445)
{return or__3824__auto____6445;
} else
{throw cljs.core.missing_protocol.call(null,"IFn.-invoke",this$);
}
}
})().call(null,this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,s);
}
});
var _invoke__20 = (function (this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,s,t){
if((function (){var and__3822__auto____6446 = this$;
if(and__3822__auto____6446)
{return this$.cljs$core$IFn$_invoke$arity$20;
} else
{return and__3822__auto____6446;
}
})())
{return this$.cljs$core$IFn$_invoke$arity$20(this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,s,t);
} else
{var x__2391__auto____6447 = (((this$ == null))?null:this$);
return (function (){var or__3824__auto____6448 = (cljs.core._invoke[goog.typeOf(x__2391__auto____6447)]);
if(or__3824__auto____6448)
{return or__3824__auto____6448;
} else
{var or__3824__auto____6449 = (cljs.core._invoke["_"]);
if(or__3824__auto____6449)
{return or__3824__auto____6449;
} else
{throw cljs.core.missing_protocol.call(null,"IFn.-invoke",this$);
}
}
})().call(null,this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,s,t);
}
});
var _invoke__21 = (function (this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,s,t,rest){
if((function (){var and__3822__auto____6450 = this$;
if(and__3822__auto____6450)
{return this$.cljs$core$IFn$_invoke$arity$21;
} else
{return and__3822__auto____6450;
}
})())
{return this$.cljs$core$IFn$_invoke$arity$21(this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,s,t,rest);
} else
{var x__2391__auto____6451 = (((this$ == null))?null:this$);
return (function (){var or__3824__auto____6452 = (cljs.core._invoke[goog.typeOf(x__2391__auto____6451)]);
if(or__3824__auto____6452)
{return or__3824__auto____6452;
} else
{var or__3824__auto____6453 = (cljs.core._invoke["_"]);
if(or__3824__auto____6453)
{return or__3824__auto____6453;
} else
{throw cljs.core.missing_protocol.call(null,"IFn.-invoke",this$);
}
}
})().call(null,this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,s,t,rest);
}
});
_invoke = function(this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,s,t,rest){
switch(arguments.length){
case 1:
return _invoke__1.call(this,this$);
case 2:
return _invoke__2.call(this,this$,a);
case 3:
return _invoke__3.call(this,this$,a,b);
case 4:
return _invoke__4.call(this,this$,a,b,c);
case 5:
return _invoke__5.call(this,this$,a,b,c,d);
case 6:
return _invoke__6.call(this,this$,a,b,c,d,e);
case 7:
return _invoke__7.call(this,this$,a,b,c,d,e,f);
case 8:
return _invoke__8.call(this,this$,a,b,c,d,e,f,g);
case 9:
return _invoke__9.call(this,this$,a,b,c,d,e,f,g,h);
case 10:
return _invoke__10.call(this,this$,a,b,c,d,e,f,g,h,i);
case 11:
return _invoke__11.call(this,this$,a,b,c,d,e,f,g,h,i,j);
case 12:
return _invoke__12.call(this,this$,a,b,c,d,e,f,g,h,i,j,k);
case 13:
return _invoke__13.call(this,this$,a,b,c,d,e,f,g,h,i,j,k,l);
case 14:
return _invoke__14.call(this,this$,a,b,c,d,e,f,g,h,i,j,k,l,m);
case 15:
return _invoke__15.call(this,this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n);
case 16:
return _invoke__16.call(this,this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o);
case 17:
return _invoke__17.call(this,this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
case 18:
return _invoke__18.call(this,this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q);
case 19:
return _invoke__19.call(this,this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,s);
case 20:
return _invoke__20.call(this,this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,s,t);
case 21:
return _invoke__21.call(this,this$,a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,s,t,rest);
}
throw('Invalid arity: ' + arguments.length);
};
_invoke.cljs$lang$arity$1 = _invoke__1;
_invoke.cljs$lang$arity$2 = _invoke__2;
_invoke.cljs$lang$arity$3 = _invoke__3;
_invoke.cljs$lang$arity$4 = _invoke__4;
_invoke.cljs$lang$arity$5 = _invoke__5;
_invoke.cljs$lang$arity$6 = _invoke__6;
_invoke.cljs$lang$arity$7 = _invoke__7;
_invoke.cljs$lang$arity$8 = _invoke__8;
_invoke.cljs$lang$arity$9 = _invoke__9;
_invoke.cljs$lang$arity$10 = _invoke__10;
_invoke.cljs$lang$arity$11 = _invoke__11;
_invoke.cljs$lang$arity$12 = _invoke__12;
_invoke.cljs$lang$arity$13 = _invoke__13;
_invoke.cljs$lang$arity$14 = _invoke__14;
_invoke.cljs$lang$arity$15 = _invoke__15;
_invoke.cljs$lang$arity$16 = _invoke__16;
_invoke.cljs$lang$arity$17 = _invoke__17;
_invoke.cljs$lang$arity$18 = _invoke__18;
_invoke.cljs$lang$arity$19 = _invoke__19;
_invoke.cljs$lang$arity$20 = _invoke__20;
_invoke.cljs$lang$arity$21 = _invoke__21;
return _invoke;
})()
;
cljs.core.ICounted = {};
cljs.core._count = (function _count(coll){
if((function (){var and__3822__auto____6458 = coll;
if(and__3822__auto____6458)
{return coll.cljs$core$ICounted$_count$arity$1;
} else
{return and__3822__auto____6458;
}
})())
{return coll.cljs$core$ICounted$_count$arity$1(coll);
} else
{var x__2391__auto____6459 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6460 = (cljs.core._count[goog.typeOf(x__2391__auto____6459)]);
if(or__3824__auto____6460)
{return or__3824__auto____6460;
} else
{var or__3824__auto____6461 = (cljs.core._count["_"]);
if(or__3824__auto____6461)
{return or__3824__auto____6461;
} else
{throw cljs.core.missing_protocol.call(null,"ICounted.-count",coll);
}
}
})().call(null,coll);
}
});
cljs.core.IEmptyableCollection = {};
cljs.core._empty = (function _empty(coll){
if((function (){var and__3822__auto____6466 = coll;
if(and__3822__auto____6466)
{return coll.cljs$core$IEmptyableCollection$_empty$arity$1;
} else
{return and__3822__auto____6466;
}
})())
{return coll.cljs$core$IEmptyableCollection$_empty$arity$1(coll);
} else
{var x__2391__auto____6467 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6468 = (cljs.core._empty[goog.typeOf(x__2391__auto____6467)]);
if(or__3824__auto____6468)
{return or__3824__auto____6468;
} else
{var or__3824__auto____6469 = (cljs.core._empty["_"]);
if(or__3824__auto____6469)
{return or__3824__auto____6469;
} else
{throw cljs.core.missing_protocol.call(null,"IEmptyableCollection.-empty",coll);
}
}
})().call(null,coll);
}
});
cljs.core.ICollection = {};
cljs.core._conj = (function _conj(coll,o){
if((function (){var and__3822__auto____6474 = coll;
if(and__3822__auto____6474)
{return coll.cljs$core$ICollection$_conj$arity$2;
} else
{return and__3822__auto____6474;
}
})())
{return coll.cljs$core$ICollection$_conj$arity$2(coll,o);
} else
{var x__2391__auto____6475 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6476 = (cljs.core._conj[goog.typeOf(x__2391__auto____6475)]);
if(or__3824__auto____6476)
{return or__3824__auto____6476;
} else
{var or__3824__auto____6477 = (cljs.core._conj["_"]);
if(or__3824__auto____6477)
{return or__3824__auto____6477;
} else
{throw cljs.core.missing_protocol.call(null,"ICollection.-conj",coll);
}
}
})().call(null,coll,o);
}
});
cljs.core.IIndexed = {};
cljs.core._nth = (function() {
var _nth = null;
var _nth__2 = (function (coll,n){
if((function (){var and__3822__auto____6486 = coll;
if(and__3822__auto____6486)
{return coll.cljs$core$IIndexed$_nth$arity$2;
} else
{return and__3822__auto____6486;
}
})())
{return coll.cljs$core$IIndexed$_nth$arity$2(coll,n);
} else
{var x__2391__auto____6487 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6488 = (cljs.core._nth[goog.typeOf(x__2391__auto____6487)]);
if(or__3824__auto____6488)
{return or__3824__auto____6488;
} else
{var or__3824__auto____6489 = (cljs.core._nth["_"]);
if(or__3824__auto____6489)
{return or__3824__auto____6489;
} else
{throw cljs.core.missing_protocol.call(null,"IIndexed.-nth",coll);
}
}
})().call(null,coll,n);
}
});
var _nth__3 = (function (coll,n,not_found){
if((function (){var and__3822__auto____6490 = coll;
if(and__3822__auto____6490)
{return coll.cljs$core$IIndexed$_nth$arity$3;
} else
{return and__3822__auto____6490;
}
})())
{return coll.cljs$core$IIndexed$_nth$arity$3(coll,n,not_found);
} else
{var x__2391__auto____6491 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6492 = (cljs.core._nth[goog.typeOf(x__2391__auto____6491)]);
if(or__3824__auto____6492)
{return or__3824__auto____6492;
} else
{var or__3824__auto____6493 = (cljs.core._nth["_"]);
if(or__3824__auto____6493)
{return or__3824__auto____6493;
} else
{throw cljs.core.missing_protocol.call(null,"IIndexed.-nth",coll);
}
}
})().call(null,coll,n,not_found);
}
});
_nth = function(coll,n,not_found){
switch(arguments.length){
case 2:
return _nth__2.call(this,coll,n);
case 3:
return _nth__3.call(this,coll,n,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
_nth.cljs$lang$arity$2 = _nth__2;
_nth.cljs$lang$arity$3 = _nth__3;
return _nth;
})()
;
cljs.core.ASeq = {};
cljs.core.ISeq = {};
cljs.core._first = (function _first(coll){
if((function (){var and__3822__auto____6498 = coll;
if(and__3822__auto____6498)
{return coll.cljs$core$ISeq$_first$arity$1;
} else
{return and__3822__auto____6498;
}
})())
{return coll.cljs$core$ISeq$_first$arity$1(coll);
} else
{var x__2391__auto____6499 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6500 = (cljs.core._first[goog.typeOf(x__2391__auto____6499)]);
if(or__3824__auto____6500)
{return or__3824__auto____6500;
} else
{var or__3824__auto____6501 = (cljs.core._first["_"]);
if(or__3824__auto____6501)
{return or__3824__auto____6501;
} else
{throw cljs.core.missing_protocol.call(null,"ISeq.-first",coll);
}
}
})().call(null,coll);
}
});
cljs.core._rest = (function _rest(coll){
if((function (){var and__3822__auto____6506 = coll;
if(and__3822__auto____6506)
{return coll.cljs$core$ISeq$_rest$arity$1;
} else
{return and__3822__auto____6506;
}
})())
{return coll.cljs$core$ISeq$_rest$arity$1(coll);
} else
{var x__2391__auto____6507 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6508 = (cljs.core._rest[goog.typeOf(x__2391__auto____6507)]);
if(or__3824__auto____6508)
{return or__3824__auto____6508;
} else
{var or__3824__auto____6509 = (cljs.core._rest["_"]);
if(or__3824__auto____6509)
{return or__3824__auto____6509;
} else
{throw cljs.core.missing_protocol.call(null,"ISeq.-rest",coll);
}
}
})().call(null,coll);
}
});
cljs.core.INext = {};
cljs.core._next = (function _next(coll){
if((function (){var and__3822__auto____6514 = coll;
if(and__3822__auto____6514)
{return coll.cljs$core$INext$_next$arity$1;
} else
{return and__3822__auto____6514;
}
})())
{return coll.cljs$core$INext$_next$arity$1(coll);
} else
{var x__2391__auto____6515 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6516 = (cljs.core._next[goog.typeOf(x__2391__auto____6515)]);
if(or__3824__auto____6516)
{return or__3824__auto____6516;
} else
{var or__3824__auto____6517 = (cljs.core._next["_"]);
if(or__3824__auto____6517)
{return or__3824__auto____6517;
} else
{throw cljs.core.missing_protocol.call(null,"INext.-next",coll);
}
}
})().call(null,coll);
}
});
cljs.core.ILookup = {};
cljs.core._lookup = (function() {
var _lookup = null;
var _lookup__2 = (function (o,k){
if((function (){var and__3822__auto____6526 = o;
if(and__3822__auto____6526)
{return o.cljs$core$ILookup$_lookup$arity$2;
} else
{return and__3822__auto____6526;
}
})())
{return o.cljs$core$ILookup$_lookup$arity$2(o,k);
} else
{var x__2391__auto____6527 = (((o == null))?null:o);
return (function (){var or__3824__auto____6528 = (cljs.core._lookup[goog.typeOf(x__2391__auto____6527)]);
if(or__3824__auto____6528)
{return or__3824__auto____6528;
} else
{var or__3824__auto____6529 = (cljs.core._lookup["_"]);
if(or__3824__auto____6529)
{return or__3824__auto____6529;
} else
{throw cljs.core.missing_protocol.call(null,"ILookup.-lookup",o);
}
}
})().call(null,o,k);
}
});
var _lookup__3 = (function (o,k,not_found){
if((function (){var and__3822__auto____6530 = o;
if(and__3822__auto____6530)
{return o.cljs$core$ILookup$_lookup$arity$3;
} else
{return and__3822__auto____6530;
}
})())
{return o.cljs$core$ILookup$_lookup$arity$3(o,k,not_found);
} else
{var x__2391__auto____6531 = (((o == null))?null:o);
return (function (){var or__3824__auto____6532 = (cljs.core._lookup[goog.typeOf(x__2391__auto____6531)]);
if(or__3824__auto____6532)
{return or__3824__auto____6532;
} else
{var or__3824__auto____6533 = (cljs.core._lookup["_"]);
if(or__3824__auto____6533)
{return or__3824__auto____6533;
} else
{throw cljs.core.missing_protocol.call(null,"ILookup.-lookup",o);
}
}
})().call(null,o,k,not_found);
}
});
_lookup = function(o,k,not_found){
switch(arguments.length){
case 2:
return _lookup__2.call(this,o,k);
case 3:
return _lookup__3.call(this,o,k,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
_lookup.cljs$lang$arity$2 = _lookup__2;
_lookup.cljs$lang$arity$3 = _lookup__3;
return _lookup;
})()
;
cljs.core.IAssociative = {};
cljs.core._contains_key_QMARK_ = (function _contains_key_QMARK_(coll,k){
if((function (){var and__3822__auto____6538 = coll;
if(and__3822__auto____6538)
{return coll.cljs$core$IAssociative$_contains_key_QMARK_$arity$2;
} else
{return and__3822__auto____6538;
}
})())
{return coll.cljs$core$IAssociative$_contains_key_QMARK_$arity$2(coll,k);
} else
{var x__2391__auto____6539 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6540 = (cljs.core._contains_key_QMARK_[goog.typeOf(x__2391__auto____6539)]);
if(or__3824__auto____6540)
{return or__3824__auto____6540;
} else
{var or__3824__auto____6541 = (cljs.core._contains_key_QMARK_["_"]);
if(or__3824__auto____6541)
{return or__3824__auto____6541;
} else
{throw cljs.core.missing_protocol.call(null,"IAssociative.-contains-key?",coll);
}
}
})().call(null,coll,k);
}
});
cljs.core._assoc = (function _assoc(coll,k,v){
if((function (){var and__3822__auto____6546 = coll;
if(and__3822__auto____6546)
{return coll.cljs$core$IAssociative$_assoc$arity$3;
} else
{return and__3822__auto____6546;
}
})())
{return coll.cljs$core$IAssociative$_assoc$arity$3(coll,k,v);
} else
{var x__2391__auto____6547 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6548 = (cljs.core._assoc[goog.typeOf(x__2391__auto____6547)]);
if(or__3824__auto____6548)
{return or__3824__auto____6548;
} else
{var or__3824__auto____6549 = (cljs.core._assoc["_"]);
if(or__3824__auto____6549)
{return or__3824__auto____6549;
} else
{throw cljs.core.missing_protocol.call(null,"IAssociative.-assoc",coll);
}
}
})().call(null,coll,k,v);
}
});
cljs.core.IMap = {};
cljs.core._dissoc = (function _dissoc(coll,k){
if((function (){var and__3822__auto____6554 = coll;
if(and__3822__auto____6554)
{return coll.cljs$core$IMap$_dissoc$arity$2;
} else
{return and__3822__auto____6554;
}
})())
{return coll.cljs$core$IMap$_dissoc$arity$2(coll,k);
} else
{var x__2391__auto____6555 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6556 = (cljs.core._dissoc[goog.typeOf(x__2391__auto____6555)]);
if(or__3824__auto____6556)
{return or__3824__auto____6556;
} else
{var or__3824__auto____6557 = (cljs.core._dissoc["_"]);
if(or__3824__auto____6557)
{return or__3824__auto____6557;
} else
{throw cljs.core.missing_protocol.call(null,"IMap.-dissoc",coll);
}
}
})().call(null,coll,k);
}
});
cljs.core.IMapEntry = {};
cljs.core._key = (function _key(coll){
if((function (){var and__3822__auto____6562 = coll;
if(and__3822__auto____6562)
{return coll.cljs$core$IMapEntry$_key$arity$1;
} else
{return and__3822__auto____6562;
}
})())
{return coll.cljs$core$IMapEntry$_key$arity$1(coll);
} else
{var x__2391__auto____6563 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6564 = (cljs.core._key[goog.typeOf(x__2391__auto____6563)]);
if(or__3824__auto____6564)
{return or__3824__auto____6564;
} else
{var or__3824__auto____6565 = (cljs.core._key["_"]);
if(or__3824__auto____6565)
{return or__3824__auto____6565;
} else
{throw cljs.core.missing_protocol.call(null,"IMapEntry.-key",coll);
}
}
})().call(null,coll);
}
});
cljs.core._val = (function _val(coll){
if((function (){var and__3822__auto____6570 = coll;
if(and__3822__auto____6570)
{return coll.cljs$core$IMapEntry$_val$arity$1;
} else
{return and__3822__auto____6570;
}
})())
{return coll.cljs$core$IMapEntry$_val$arity$1(coll);
} else
{var x__2391__auto____6571 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6572 = (cljs.core._val[goog.typeOf(x__2391__auto____6571)]);
if(or__3824__auto____6572)
{return or__3824__auto____6572;
} else
{var or__3824__auto____6573 = (cljs.core._val["_"]);
if(or__3824__auto____6573)
{return or__3824__auto____6573;
} else
{throw cljs.core.missing_protocol.call(null,"IMapEntry.-val",coll);
}
}
})().call(null,coll);
}
});
cljs.core.ISet = {};
cljs.core._disjoin = (function _disjoin(coll,v){
if((function (){var and__3822__auto____6578 = coll;
if(and__3822__auto____6578)
{return coll.cljs$core$ISet$_disjoin$arity$2;
} else
{return and__3822__auto____6578;
}
})())
{return coll.cljs$core$ISet$_disjoin$arity$2(coll,v);
} else
{var x__2391__auto____6579 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6580 = (cljs.core._disjoin[goog.typeOf(x__2391__auto____6579)]);
if(or__3824__auto____6580)
{return or__3824__auto____6580;
} else
{var or__3824__auto____6581 = (cljs.core._disjoin["_"]);
if(or__3824__auto____6581)
{return or__3824__auto____6581;
} else
{throw cljs.core.missing_protocol.call(null,"ISet.-disjoin",coll);
}
}
})().call(null,coll,v);
}
});
cljs.core.IStack = {};
cljs.core._peek = (function _peek(coll){
if((function (){var and__3822__auto____6586 = coll;
if(and__3822__auto____6586)
{return coll.cljs$core$IStack$_peek$arity$1;
} else
{return and__3822__auto____6586;
}
})())
{return coll.cljs$core$IStack$_peek$arity$1(coll);
} else
{var x__2391__auto____6587 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6588 = (cljs.core._peek[goog.typeOf(x__2391__auto____6587)]);
if(or__3824__auto____6588)
{return or__3824__auto____6588;
} else
{var or__3824__auto____6589 = (cljs.core._peek["_"]);
if(or__3824__auto____6589)
{return or__3824__auto____6589;
} else
{throw cljs.core.missing_protocol.call(null,"IStack.-peek",coll);
}
}
})().call(null,coll);
}
});
cljs.core._pop = (function _pop(coll){
if((function (){var and__3822__auto____6594 = coll;
if(and__3822__auto____6594)
{return coll.cljs$core$IStack$_pop$arity$1;
} else
{return and__3822__auto____6594;
}
})())
{return coll.cljs$core$IStack$_pop$arity$1(coll);
} else
{var x__2391__auto____6595 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6596 = (cljs.core._pop[goog.typeOf(x__2391__auto____6595)]);
if(or__3824__auto____6596)
{return or__3824__auto____6596;
} else
{var or__3824__auto____6597 = (cljs.core._pop["_"]);
if(or__3824__auto____6597)
{return or__3824__auto____6597;
} else
{throw cljs.core.missing_protocol.call(null,"IStack.-pop",coll);
}
}
})().call(null,coll);
}
});
cljs.core.IVector = {};
cljs.core._assoc_n = (function _assoc_n(coll,n,val){
if((function (){var and__3822__auto____6602 = coll;
if(and__3822__auto____6602)
{return coll.cljs$core$IVector$_assoc_n$arity$3;
} else
{return and__3822__auto____6602;
}
})())
{return coll.cljs$core$IVector$_assoc_n$arity$3(coll,n,val);
} else
{var x__2391__auto____6603 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6604 = (cljs.core._assoc_n[goog.typeOf(x__2391__auto____6603)]);
if(or__3824__auto____6604)
{return or__3824__auto____6604;
} else
{var or__3824__auto____6605 = (cljs.core._assoc_n["_"]);
if(or__3824__auto____6605)
{return or__3824__auto____6605;
} else
{throw cljs.core.missing_protocol.call(null,"IVector.-assoc-n",coll);
}
}
})().call(null,coll,n,val);
}
});
cljs.core.IDeref = {};
cljs.core._deref = (function _deref(o){
if((function (){var and__3822__auto____6610 = o;
if(and__3822__auto____6610)
{return o.cljs$core$IDeref$_deref$arity$1;
} else
{return and__3822__auto____6610;
}
})())
{return o.cljs$core$IDeref$_deref$arity$1(o);
} else
{var x__2391__auto____6611 = (((o == null))?null:o);
return (function (){var or__3824__auto____6612 = (cljs.core._deref[goog.typeOf(x__2391__auto____6611)]);
if(or__3824__auto____6612)
{return or__3824__auto____6612;
} else
{var or__3824__auto____6613 = (cljs.core._deref["_"]);
if(or__3824__auto____6613)
{return or__3824__auto____6613;
} else
{throw cljs.core.missing_protocol.call(null,"IDeref.-deref",o);
}
}
})().call(null,o);
}
});
cljs.core.IDerefWithTimeout = {};
cljs.core._deref_with_timeout = (function _deref_with_timeout(o,msec,timeout_val){
if((function (){var and__3822__auto____6618 = o;
if(and__3822__auto____6618)
{return o.cljs$core$IDerefWithTimeout$_deref_with_timeout$arity$3;
} else
{return and__3822__auto____6618;
}
})())
{return o.cljs$core$IDerefWithTimeout$_deref_with_timeout$arity$3(o,msec,timeout_val);
} else
{var x__2391__auto____6619 = (((o == null))?null:o);
return (function (){var or__3824__auto____6620 = (cljs.core._deref_with_timeout[goog.typeOf(x__2391__auto____6619)]);
if(or__3824__auto____6620)
{return or__3824__auto____6620;
} else
{var or__3824__auto____6621 = (cljs.core._deref_with_timeout["_"]);
if(or__3824__auto____6621)
{return or__3824__auto____6621;
} else
{throw cljs.core.missing_protocol.call(null,"IDerefWithTimeout.-deref-with-timeout",o);
}
}
})().call(null,o,msec,timeout_val);
}
});
cljs.core.IMeta = {};
cljs.core._meta = (function _meta(o){
if((function (){var and__3822__auto____6626 = o;
if(and__3822__auto____6626)
{return o.cljs$core$IMeta$_meta$arity$1;
} else
{return and__3822__auto____6626;
}
})())
{return o.cljs$core$IMeta$_meta$arity$1(o);
} else
{var x__2391__auto____6627 = (((o == null))?null:o);
return (function (){var or__3824__auto____6628 = (cljs.core._meta[goog.typeOf(x__2391__auto____6627)]);
if(or__3824__auto____6628)
{return or__3824__auto____6628;
} else
{var or__3824__auto____6629 = (cljs.core._meta["_"]);
if(or__3824__auto____6629)
{return or__3824__auto____6629;
} else
{throw cljs.core.missing_protocol.call(null,"IMeta.-meta",o);
}
}
})().call(null,o);
}
});
cljs.core.IWithMeta = {};
cljs.core._with_meta = (function _with_meta(o,meta){
if((function (){var and__3822__auto____6634 = o;
if(and__3822__auto____6634)
{return o.cljs$core$IWithMeta$_with_meta$arity$2;
} else
{return and__3822__auto____6634;
}
})())
{return o.cljs$core$IWithMeta$_with_meta$arity$2(o,meta);
} else
{var x__2391__auto____6635 = (((o == null))?null:o);
return (function (){var or__3824__auto____6636 = (cljs.core._with_meta[goog.typeOf(x__2391__auto____6635)]);
if(or__3824__auto____6636)
{return or__3824__auto____6636;
} else
{var or__3824__auto____6637 = (cljs.core._with_meta["_"]);
if(or__3824__auto____6637)
{return or__3824__auto____6637;
} else
{throw cljs.core.missing_protocol.call(null,"IWithMeta.-with-meta",o);
}
}
})().call(null,o,meta);
}
});
cljs.core.IReduce = {};
cljs.core._reduce = (function() {
var _reduce = null;
var _reduce__2 = (function (coll,f){
if((function (){var and__3822__auto____6646 = coll;
if(and__3822__auto____6646)
{return coll.cljs$core$IReduce$_reduce$arity$2;
} else
{return and__3822__auto____6646;
}
})())
{return coll.cljs$core$IReduce$_reduce$arity$2(coll,f);
} else
{var x__2391__auto____6647 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6648 = (cljs.core._reduce[goog.typeOf(x__2391__auto____6647)]);
if(or__3824__auto____6648)
{return or__3824__auto____6648;
} else
{var or__3824__auto____6649 = (cljs.core._reduce["_"]);
if(or__3824__auto____6649)
{return or__3824__auto____6649;
} else
{throw cljs.core.missing_protocol.call(null,"IReduce.-reduce",coll);
}
}
})().call(null,coll,f);
}
});
var _reduce__3 = (function (coll,f,start){
if((function (){var and__3822__auto____6650 = coll;
if(and__3822__auto____6650)
{return coll.cljs$core$IReduce$_reduce$arity$3;
} else
{return and__3822__auto____6650;
}
})())
{return coll.cljs$core$IReduce$_reduce$arity$3(coll,f,start);
} else
{var x__2391__auto____6651 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6652 = (cljs.core._reduce[goog.typeOf(x__2391__auto____6651)]);
if(or__3824__auto____6652)
{return or__3824__auto____6652;
} else
{var or__3824__auto____6653 = (cljs.core._reduce["_"]);
if(or__3824__auto____6653)
{return or__3824__auto____6653;
} else
{throw cljs.core.missing_protocol.call(null,"IReduce.-reduce",coll);
}
}
})().call(null,coll,f,start);
}
});
_reduce = function(coll,f,start){
switch(arguments.length){
case 2:
return _reduce__2.call(this,coll,f);
case 3:
return _reduce__3.call(this,coll,f,start);
}
throw('Invalid arity: ' + arguments.length);
};
_reduce.cljs$lang$arity$2 = _reduce__2;
_reduce.cljs$lang$arity$3 = _reduce__3;
return _reduce;
})()
;
cljs.core.IKVReduce = {};
cljs.core._kv_reduce = (function _kv_reduce(coll,f,init){
if((function (){var and__3822__auto____6658 = coll;
if(and__3822__auto____6658)
{return coll.cljs$core$IKVReduce$_kv_reduce$arity$3;
} else
{return and__3822__auto____6658;
}
})())
{return coll.cljs$core$IKVReduce$_kv_reduce$arity$3(coll,f,init);
} else
{var x__2391__auto____6659 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6660 = (cljs.core._kv_reduce[goog.typeOf(x__2391__auto____6659)]);
if(or__3824__auto____6660)
{return or__3824__auto____6660;
} else
{var or__3824__auto____6661 = (cljs.core._kv_reduce["_"]);
if(or__3824__auto____6661)
{return or__3824__auto____6661;
} else
{throw cljs.core.missing_protocol.call(null,"IKVReduce.-kv-reduce",coll);
}
}
})().call(null,coll,f,init);
}
});
cljs.core.IEquiv = {};
cljs.core._equiv = (function _equiv(o,other){
if((function (){var and__3822__auto____6666 = o;
if(and__3822__auto____6666)
{return o.cljs$core$IEquiv$_equiv$arity$2;
} else
{return and__3822__auto____6666;
}
})())
{return o.cljs$core$IEquiv$_equiv$arity$2(o,other);
} else
{var x__2391__auto____6667 = (((o == null))?null:o);
return (function (){var or__3824__auto____6668 = (cljs.core._equiv[goog.typeOf(x__2391__auto____6667)]);
if(or__3824__auto____6668)
{return or__3824__auto____6668;
} else
{var or__3824__auto____6669 = (cljs.core._equiv["_"]);
if(or__3824__auto____6669)
{return or__3824__auto____6669;
} else
{throw cljs.core.missing_protocol.call(null,"IEquiv.-equiv",o);
}
}
})().call(null,o,other);
}
});
cljs.core.IHash = {};
cljs.core._hash = (function _hash(o){
if((function (){var and__3822__auto____6674 = o;
if(and__3822__auto____6674)
{return o.cljs$core$IHash$_hash$arity$1;
} else
{return and__3822__auto____6674;
}
})())
{return o.cljs$core$IHash$_hash$arity$1(o);
} else
{var x__2391__auto____6675 = (((o == null))?null:o);
return (function (){var or__3824__auto____6676 = (cljs.core._hash[goog.typeOf(x__2391__auto____6675)]);
if(or__3824__auto____6676)
{return or__3824__auto____6676;
} else
{var or__3824__auto____6677 = (cljs.core._hash["_"]);
if(or__3824__auto____6677)
{return or__3824__auto____6677;
} else
{throw cljs.core.missing_protocol.call(null,"IHash.-hash",o);
}
}
})().call(null,o);
}
});
cljs.core.ISeqable = {};
cljs.core._seq = (function _seq(o){
if((function (){var and__3822__auto____6682 = o;
if(and__3822__auto____6682)
{return o.cljs$core$ISeqable$_seq$arity$1;
} else
{return and__3822__auto____6682;
}
})())
{return o.cljs$core$ISeqable$_seq$arity$1(o);
} else
{var x__2391__auto____6683 = (((o == null))?null:o);
return (function (){var or__3824__auto____6684 = (cljs.core._seq[goog.typeOf(x__2391__auto____6683)]);
if(or__3824__auto____6684)
{return or__3824__auto____6684;
} else
{var or__3824__auto____6685 = (cljs.core._seq["_"]);
if(or__3824__auto____6685)
{return or__3824__auto____6685;
} else
{throw cljs.core.missing_protocol.call(null,"ISeqable.-seq",o);
}
}
})().call(null,o);
}
});
cljs.core.ISequential = {};
cljs.core.IList = {};
cljs.core.IRecord = {};
cljs.core.IReversible = {};
cljs.core._rseq = (function _rseq(coll){
if((function (){var and__3822__auto____6690 = coll;
if(and__3822__auto____6690)
{return coll.cljs$core$IReversible$_rseq$arity$1;
} else
{return and__3822__auto____6690;
}
})())
{return coll.cljs$core$IReversible$_rseq$arity$1(coll);
} else
{var x__2391__auto____6691 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6692 = (cljs.core._rseq[goog.typeOf(x__2391__auto____6691)]);
if(or__3824__auto____6692)
{return or__3824__auto____6692;
} else
{var or__3824__auto____6693 = (cljs.core._rseq["_"]);
if(or__3824__auto____6693)
{return or__3824__auto____6693;
} else
{throw cljs.core.missing_protocol.call(null,"IReversible.-rseq",coll);
}
}
})().call(null,coll);
}
});
cljs.core.ISorted = {};
cljs.core._sorted_seq = (function _sorted_seq(coll,ascending_QMARK_){
if((function (){var and__3822__auto____6698 = coll;
if(and__3822__auto____6698)
{return coll.cljs$core$ISorted$_sorted_seq$arity$2;
} else
{return and__3822__auto____6698;
}
})())
{return coll.cljs$core$ISorted$_sorted_seq$arity$2(coll,ascending_QMARK_);
} else
{var x__2391__auto____6699 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6700 = (cljs.core._sorted_seq[goog.typeOf(x__2391__auto____6699)]);
if(or__3824__auto____6700)
{return or__3824__auto____6700;
} else
{var or__3824__auto____6701 = (cljs.core._sorted_seq["_"]);
if(or__3824__auto____6701)
{return or__3824__auto____6701;
} else
{throw cljs.core.missing_protocol.call(null,"ISorted.-sorted-seq",coll);
}
}
})().call(null,coll,ascending_QMARK_);
}
});
cljs.core._sorted_seq_from = (function _sorted_seq_from(coll,k,ascending_QMARK_){
if((function (){var and__3822__auto____6706 = coll;
if(and__3822__auto____6706)
{return coll.cljs$core$ISorted$_sorted_seq_from$arity$3;
} else
{return and__3822__auto____6706;
}
})())
{return coll.cljs$core$ISorted$_sorted_seq_from$arity$3(coll,k,ascending_QMARK_);
} else
{var x__2391__auto____6707 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6708 = (cljs.core._sorted_seq_from[goog.typeOf(x__2391__auto____6707)]);
if(or__3824__auto____6708)
{return or__3824__auto____6708;
} else
{var or__3824__auto____6709 = (cljs.core._sorted_seq_from["_"]);
if(or__3824__auto____6709)
{return or__3824__auto____6709;
} else
{throw cljs.core.missing_protocol.call(null,"ISorted.-sorted-seq-from",coll);
}
}
})().call(null,coll,k,ascending_QMARK_);
}
});
cljs.core._entry_key = (function _entry_key(coll,entry){
if((function (){var and__3822__auto____6714 = coll;
if(and__3822__auto____6714)
{return coll.cljs$core$ISorted$_entry_key$arity$2;
} else
{return and__3822__auto____6714;
}
})())
{return coll.cljs$core$ISorted$_entry_key$arity$2(coll,entry);
} else
{var x__2391__auto____6715 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6716 = (cljs.core._entry_key[goog.typeOf(x__2391__auto____6715)]);
if(or__3824__auto____6716)
{return or__3824__auto____6716;
} else
{var or__3824__auto____6717 = (cljs.core._entry_key["_"]);
if(or__3824__auto____6717)
{return or__3824__auto____6717;
} else
{throw cljs.core.missing_protocol.call(null,"ISorted.-entry-key",coll);
}
}
})().call(null,coll,entry);
}
});
cljs.core._comparator = (function _comparator(coll){
if((function (){var and__3822__auto____6722 = coll;
if(and__3822__auto____6722)
{return coll.cljs$core$ISorted$_comparator$arity$1;
} else
{return and__3822__auto____6722;
}
})())
{return coll.cljs$core$ISorted$_comparator$arity$1(coll);
} else
{var x__2391__auto____6723 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6724 = (cljs.core._comparator[goog.typeOf(x__2391__auto____6723)]);
if(or__3824__auto____6724)
{return or__3824__auto____6724;
} else
{var or__3824__auto____6725 = (cljs.core._comparator["_"]);
if(or__3824__auto____6725)
{return or__3824__auto____6725;
} else
{throw cljs.core.missing_protocol.call(null,"ISorted.-comparator",coll);
}
}
})().call(null,coll);
}
});
cljs.core.IPrintable = {};
cljs.core._pr_seq = (function _pr_seq(o,opts){
if((function (){var and__3822__auto____6730 = o;
if(and__3822__auto____6730)
{return o.cljs$core$IPrintable$_pr_seq$arity$2;
} else
{return and__3822__auto____6730;
}
})())
{return o.cljs$core$IPrintable$_pr_seq$arity$2(o,opts);
} else
{var x__2391__auto____6731 = (((o == null))?null:o);
return (function (){var or__3824__auto____6732 = (cljs.core._pr_seq[goog.typeOf(x__2391__auto____6731)]);
if(or__3824__auto____6732)
{return or__3824__auto____6732;
} else
{var or__3824__auto____6733 = (cljs.core._pr_seq["_"]);
if(or__3824__auto____6733)
{return or__3824__auto____6733;
} else
{throw cljs.core.missing_protocol.call(null,"IPrintable.-pr-seq",o);
}
}
})().call(null,o,opts);
}
});
cljs.core.IPending = {};
cljs.core._realized_QMARK_ = (function _realized_QMARK_(d){
if((function (){var and__3822__auto____6738 = d;
if(and__3822__auto____6738)
{return d.cljs$core$IPending$_realized_QMARK_$arity$1;
} else
{return and__3822__auto____6738;
}
})())
{return d.cljs$core$IPending$_realized_QMARK_$arity$1(d);
} else
{var x__2391__auto____6739 = (((d == null))?null:d);
return (function (){var or__3824__auto____6740 = (cljs.core._realized_QMARK_[goog.typeOf(x__2391__auto____6739)]);
if(or__3824__auto____6740)
{return or__3824__auto____6740;
} else
{var or__3824__auto____6741 = (cljs.core._realized_QMARK_["_"]);
if(or__3824__auto____6741)
{return or__3824__auto____6741;
} else
{throw cljs.core.missing_protocol.call(null,"IPending.-realized?",d);
}
}
})().call(null,d);
}
});
cljs.core.IWatchable = {};
cljs.core._notify_watches = (function _notify_watches(this$,oldval,newval){
if((function (){var and__3822__auto____6746 = this$;
if(and__3822__auto____6746)
{return this$.cljs$core$IWatchable$_notify_watches$arity$3;
} else
{return and__3822__auto____6746;
}
})())
{return this$.cljs$core$IWatchable$_notify_watches$arity$3(this$,oldval,newval);
} else
{var x__2391__auto____6747 = (((this$ == null))?null:this$);
return (function (){var or__3824__auto____6748 = (cljs.core._notify_watches[goog.typeOf(x__2391__auto____6747)]);
if(or__3824__auto____6748)
{return or__3824__auto____6748;
} else
{var or__3824__auto____6749 = (cljs.core._notify_watches["_"]);
if(or__3824__auto____6749)
{return or__3824__auto____6749;
} else
{throw cljs.core.missing_protocol.call(null,"IWatchable.-notify-watches",this$);
}
}
})().call(null,this$,oldval,newval);
}
});
cljs.core._add_watch = (function _add_watch(this$,key,f){
if((function (){var and__3822__auto____6754 = this$;
if(and__3822__auto____6754)
{return this$.cljs$core$IWatchable$_add_watch$arity$3;
} else
{return and__3822__auto____6754;
}
})())
{return this$.cljs$core$IWatchable$_add_watch$arity$3(this$,key,f);
} else
{var x__2391__auto____6755 = (((this$ == null))?null:this$);
return (function (){var or__3824__auto____6756 = (cljs.core._add_watch[goog.typeOf(x__2391__auto____6755)]);
if(or__3824__auto____6756)
{return or__3824__auto____6756;
} else
{var or__3824__auto____6757 = (cljs.core._add_watch["_"]);
if(or__3824__auto____6757)
{return or__3824__auto____6757;
} else
{throw cljs.core.missing_protocol.call(null,"IWatchable.-add-watch",this$);
}
}
})().call(null,this$,key,f);
}
});
cljs.core._remove_watch = (function _remove_watch(this$,key){
if((function (){var and__3822__auto____6762 = this$;
if(and__3822__auto____6762)
{return this$.cljs$core$IWatchable$_remove_watch$arity$2;
} else
{return and__3822__auto____6762;
}
})())
{return this$.cljs$core$IWatchable$_remove_watch$arity$2(this$,key);
} else
{var x__2391__auto____6763 = (((this$ == null))?null:this$);
return (function (){var or__3824__auto____6764 = (cljs.core._remove_watch[goog.typeOf(x__2391__auto____6763)]);
if(or__3824__auto____6764)
{return or__3824__auto____6764;
} else
{var or__3824__auto____6765 = (cljs.core._remove_watch["_"]);
if(or__3824__auto____6765)
{return or__3824__auto____6765;
} else
{throw cljs.core.missing_protocol.call(null,"IWatchable.-remove-watch",this$);
}
}
})().call(null,this$,key);
}
});
cljs.core.IEditableCollection = {};
cljs.core._as_transient = (function _as_transient(coll){
if((function (){var and__3822__auto____6770 = coll;
if(and__3822__auto____6770)
{return coll.cljs$core$IEditableCollection$_as_transient$arity$1;
} else
{return and__3822__auto____6770;
}
})())
{return coll.cljs$core$IEditableCollection$_as_transient$arity$1(coll);
} else
{var x__2391__auto____6771 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6772 = (cljs.core._as_transient[goog.typeOf(x__2391__auto____6771)]);
if(or__3824__auto____6772)
{return or__3824__auto____6772;
} else
{var or__3824__auto____6773 = (cljs.core._as_transient["_"]);
if(or__3824__auto____6773)
{return or__3824__auto____6773;
} else
{throw cljs.core.missing_protocol.call(null,"IEditableCollection.-as-transient",coll);
}
}
})().call(null,coll);
}
});
cljs.core.ITransientCollection = {};
cljs.core._conj_BANG_ = (function _conj_BANG_(tcoll,val){
if((function (){var and__3822__auto____6778 = tcoll;
if(and__3822__auto____6778)
{return tcoll.cljs$core$ITransientCollection$_conj_BANG_$arity$2;
} else
{return and__3822__auto____6778;
}
})())
{return tcoll.cljs$core$ITransientCollection$_conj_BANG_$arity$2(tcoll,val);
} else
{var x__2391__auto____6779 = (((tcoll == null))?null:tcoll);
return (function (){var or__3824__auto____6780 = (cljs.core._conj_BANG_[goog.typeOf(x__2391__auto____6779)]);
if(or__3824__auto____6780)
{return or__3824__auto____6780;
} else
{var or__3824__auto____6781 = (cljs.core._conj_BANG_["_"]);
if(or__3824__auto____6781)
{return or__3824__auto____6781;
} else
{throw cljs.core.missing_protocol.call(null,"ITransientCollection.-conj!",tcoll);
}
}
})().call(null,tcoll,val);
}
});
cljs.core._persistent_BANG_ = (function _persistent_BANG_(tcoll){
if((function (){var and__3822__auto____6786 = tcoll;
if(and__3822__auto____6786)
{return tcoll.cljs$core$ITransientCollection$_persistent_BANG_$arity$1;
} else
{return and__3822__auto____6786;
}
})())
{return tcoll.cljs$core$ITransientCollection$_persistent_BANG_$arity$1(tcoll);
} else
{var x__2391__auto____6787 = (((tcoll == null))?null:tcoll);
return (function (){var or__3824__auto____6788 = (cljs.core._persistent_BANG_[goog.typeOf(x__2391__auto____6787)]);
if(or__3824__auto____6788)
{return or__3824__auto____6788;
} else
{var or__3824__auto____6789 = (cljs.core._persistent_BANG_["_"]);
if(or__3824__auto____6789)
{return or__3824__auto____6789;
} else
{throw cljs.core.missing_protocol.call(null,"ITransientCollection.-persistent!",tcoll);
}
}
})().call(null,tcoll);
}
});
cljs.core.ITransientAssociative = {};
cljs.core._assoc_BANG_ = (function _assoc_BANG_(tcoll,key,val){
if((function (){var and__3822__auto____6794 = tcoll;
if(and__3822__auto____6794)
{return tcoll.cljs$core$ITransientAssociative$_assoc_BANG_$arity$3;
} else
{return and__3822__auto____6794;
}
})())
{return tcoll.cljs$core$ITransientAssociative$_assoc_BANG_$arity$3(tcoll,key,val);
} else
{var x__2391__auto____6795 = (((tcoll == null))?null:tcoll);
return (function (){var or__3824__auto____6796 = (cljs.core._assoc_BANG_[goog.typeOf(x__2391__auto____6795)]);
if(or__3824__auto____6796)
{return or__3824__auto____6796;
} else
{var or__3824__auto____6797 = (cljs.core._assoc_BANG_["_"]);
if(or__3824__auto____6797)
{return or__3824__auto____6797;
} else
{throw cljs.core.missing_protocol.call(null,"ITransientAssociative.-assoc!",tcoll);
}
}
})().call(null,tcoll,key,val);
}
});
cljs.core.ITransientMap = {};
cljs.core._dissoc_BANG_ = (function _dissoc_BANG_(tcoll,key){
if((function (){var and__3822__auto____6802 = tcoll;
if(and__3822__auto____6802)
{return tcoll.cljs$core$ITransientMap$_dissoc_BANG_$arity$2;
} else
{return and__3822__auto____6802;
}
})())
{return tcoll.cljs$core$ITransientMap$_dissoc_BANG_$arity$2(tcoll,key);
} else
{var x__2391__auto____6803 = (((tcoll == null))?null:tcoll);
return (function (){var or__3824__auto____6804 = (cljs.core._dissoc_BANG_[goog.typeOf(x__2391__auto____6803)]);
if(or__3824__auto____6804)
{return or__3824__auto____6804;
} else
{var or__3824__auto____6805 = (cljs.core._dissoc_BANG_["_"]);
if(or__3824__auto____6805)
{return or__3824__auto____6805;
} else
{throw cljs.core.missing_protocol.call(null,"ITransientMap.-dissoc!",tcoll);
}
}
})().call(null,tcoll,key);
}
});
cljs.core.ITransientVector = {};
cljs.core._assoc_n_BANG_ = (function _assoc_n_BANG_(tcoll,n,val){
if((function (){var and__3822__auto____6810 = tcoll;
if(and__3822__auto____6810)
{return tcoll.cljs$core$ITransientVector$_assoc_n_BANG_$arity$3;
} else
{return and__3822__auto____6810;
}
})())
{return tcoll.cljs$core$ITransientVector$_assoc_n_BANG_$arity$3(tcoll,n,val);
} else
{var x__2391__auto____6811 = (((tcoll == null))?null:tcoll);
return (function (){var or__3824__auto____6812 = (cljs.core._assoc_n_BANG_[goog.typeOf(x__2391__auto____6811)]);
if(or__3824__auto____6812)
{return or__3824__auto____6812;
} else
{var or__3824__auto____6813 = (cljs.core._assoc_n_BANG_["_"]);
if(or__3824__auto____6813)
{return or__3824__auto____6813;
} else
{throw cljs.core.missing_protocol.call(null,"ITransientVector.-assoc-n!",tcoll);
}
}
})().call(null,tcoll,n,val);
}
});
cljs.core._pop_BANG_ = (function _pop_BANG_(tcoll){
if((function (){var and__3822__auto____6818 = tcoll;
if(and__3822__auto____6818)
{return tcoll.cljs$core$ITransientVector$_pop_BANG_$arity$1;
} else
{return and__3822__auto____6818;
}
})())
{return tcoll.cljs$core$ITransientVector$_pop_BANG_$arity$1(tcoll);
} else
{var x__2391__auto____6819 = (((tcoll == null))?null:tcoll);
return (function (){var or__3824__auto____6820 = (cljs.core._pop_BANG_[goog.typeOf(x__2391__auto____6819)]);
if(or__3824__auto____6820)
{return or__3824__auto____6820;
} else
{var or__3824__auto____6821 = (cljs.core._pop_BANG_["_"]);
if(or__3824__auto____6821)
{return or__3824__auto____6821;
} else
{throw cljs.core.missing_protocol.call(null,"ITransientVector.-pop!",tcoll);
}
}
})().call(null,tcoll);
}
});
cljs.core.ITransientSet = {};
cljs.core._disjoin_BANG_ = (function _disjoin_BANG_(tcoll,v){
if((function (){var and__3822__auto____6826 = tcoll;
if(and__3822__auto____6826)
{return tcoll.cljs$core$ITransientSet$_disjoin_BANG_$arity$2;
} else
{return and__3822__auto____6826;
}
})())
{return tcoll.cljs$core$ITransientSet$_disjoin_BANG_$arity$2(tcoll,v);
} else
{var x__2391__auto____6827 = (((tcoll == null))?null:tcoll);
return (function (){var or__3824__auto____6828 = (cljs.core._disjoin_BANG_[goog.typeOf(x__2391__auto____6827)]);
if(or__3824__auto____6828)
{return or__3824__auto____6828;
} else
{var or__3824__auto____6829 = (cljs.core._disjoin_BANG_["_"]);
if(or__3824__auto____6829)
{return or__3824__auto____6829;
} else
{throw cljs.core.missing_protocol.call(null,"ITransientSet.-disjoin!",tcoll);
}
}
})().call(null,tcoll,v);
}
});
cljs.core.IComparable = {};
cljs.core._compare = (function _compare(x,y){
if((function (){var and__3822__auto____6834 = x;
if(and__3822__auto____6834)
{return x.cljs$core$IComparable$_compare$arity$2;
} else
{return and__3822__auto____6834;
}
})())
{return x.cljs$core$IComparable$_compare$arity$2(x,y);
} else
{var x__2391__auto____6835 = (((x == null))?null:x);
return (function (){var or__3824__auto____6836 = (cljs.core._compare[goog.typeOf(x__2391__auto____6835)]);
if(or__3824__auto____6836)
{return or__3824__auto____6836;
} else
{var or__3824__auto____6837 = (cljs.core._compare["_"]);
if(or__3824__auto____6837)
{return or__3824__auto____6837;
} else
{throw cljs.core.missing_protocol.call(null,"IComparable.-compare",x);
}
}
})().call(null,x,y);
}
});
cljs.core.IChunk = {};
cljs.core._drop_first = (function _drop_first(coll){
if((function (){var and__3822__auto____6842 = coll;
if(and__3822__auto____6842)
{return coll.cljs$core$IChunk$_drop_first$arity$1;
} else
{return and__3822__auto____6842;
}
})())
{return coll.cljs$core$IChunk$_drop_first$arity$1(coll);
} else
{var x__2391__auto____6843 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6844 = (cljs.core._drop_first[goog.typeOf(x__2391__auto____6843)]);
if(or__3824__auto____6844)
{return or__3824__auto____6844;
} else
{var or__3824__auto____6845 = (cljs.core._drop_first["_"]);
if(or__3824__auto____6845)
{return or__3824__auto____6845;
} else
{throw cljs.core.missing_protocol.call(null,"IChunk.-drop-first",coll);
}
}
})().call(null,coll);
}
});
cljs.core.IChunkedSeq = {};
cljs.core._chunked_first = (function _chunked_first(coll){
if((function (){var and__3822__auto____6850 = coll;
if(and__3822__auto____6850)
{return coll.cljs$core$IChunkedSeq$_chunked_first$arity$1;
} else
{return and__3822__auto____6850;
}
})())
{return coll.cljs$core$IChunkedSeq$_chunked_first$arity$1(coll);
} else
{var x__2391__auto____6851 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6852 = (cljs.core._chunked_first[goog.typeOf(x__2391__auto____6851)]);
if(or__3824__auto____6852)
{return or__3824__auto____6852;
} else
{var or__3824__auto____6853 = (cljs.core._chunked_first["_"]);
if(or__3824__auto____6853)
{return or__3824__auto____6853;
} else
{throw cljs.core.missing_protocol.call(null,"IChunkedSeq.-chunked-first",coll);
}
}
})().call(null,coll);
}
});
cljs.core._chunked_rest = (function _chunked_rest(coll){
if((function (){var and__3822__auto____6858 = coll;
if(and__3822__auto____6858)
{return coll.cljs$core$IChunkedSeq$_chunked_rest$arity$1;
} else
{return and__3822__auto____6858;
}
})())
{return coll.cljs$core$IChunkedSeq$_chunked_rest$arity$1(coll);
} else
{var x__2391__auto____6859 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6860 = (cljs.core._chunked_rest[goog.typeOf(x__2391__auto____6859)]);
if(or__3824__auto____6860)
{return or__3824__auto____6860;
} else
{var or__3824__auto____6861 = (cljs.core._chunked_rest["_"]);
if(or__3824__auto____6861)
{return or__3824__auto____6861;
} else
{throw cljs.core.missing_protocol.call(null,"IChunkedSeq.-chunked-rest",coll);
}
}
})().call(null,coll);
}
});
cljs.core.IChunkedNext = {};
cljs.core._chunked_next = (function _chunked_next(coll){
if((function (){var and__3822__auto____6866 = coll;
if(and__3822__auto____6866)
{return coll.cljs$core$IChunkedNext$_chunked_next$arity$1;
} else
{return and__3822__auto____6866;
}
})())
{return coll.cljs$core$IChunkedNext$_chunked_next$arity$1(coll);
} else
{var x__2391__auto____6867 = (((coll == null))?null:coll);
return (function (){var or__3824__auto____6868 = (cljs.core._chunked_next[goog.typeOf(x__2391__auto____6867)]);
if(or__3824__auto____6868)
{return or__3824__auto____6868;
} else
{var or__3824__auto____6869 = (cljs.core._chunked_next["_"]);
if(or__3824__auto____6869)
{return or__3824__auto____6869;
} else
{throw cljs.core.missing_protocol.call(null,"IChunkedNext.-chunked-next",coll);
}
}
})().call(null,coll);
}
});
/**
* Tests if 2 arguments are the same object
*/
cljs.core.identical_QMARK_ = (function identical_QMARK_(x,y){
return (x === y);
});
/**
* Equality. Returns true if x equals y, false if not. Compares
* numbers and collections in a type-independent manner.  Clojure's immutable data
* structures define -equiv (and thus =) as a value, not an identity,
* comparison.
* @param {...*} var_args
*/
cljs.core._EQ_ = (function() {
var _EQ_ = null;
var _EQ___1 = (function (x){
return true;
});
var _EQ___2 = (function (x,y){
var or__3824__auto____6871 = (x === y);
if(or__3824__auto____6871)
{return or__3824__auto____6871;
} else
{return cljs.core._equiv.call(null,x,y);
}
});
var _EQ___3 = (function() { 
var G__6872__delegate = function (x,y,more){
while(true){
if(cljs.core.truth_(_EQ_.call(null,x,y)))
{if(cljs.core.next.call(null,more))
{{
var G__6873 = y;
var G__6874 = cljs.core.first.call(null,more);
var G__6875 = cljs.core.next.call(null,more);
x = G__6873;
y = G__6874;
more = G__6875;
continue;
}
} else
{return _EQ_.call(null,y,cljs.core.first.call(null,more));
}
} else
{return false;
}
break;
}
};
var G__6872 = function (x,y,var_args){
var more = null;
if (goog.isDef(var_args)) {
  more = cljs.core.array_seq(Array.prototype.slice.call(arguments, 2),0);
} 
return G__6872__delegate.call(this, x, y, more);
};
G__6872.cljs$lang$maxFixedArity = 2;
G__6872.cljs$lang$applyTo = (function (arglist__6876){
var x = cljs.core.first(arglist__6876);
var y = cljs.core.first(cljs.core.next(arglist__6876));
var more = cljs.core.rest(cljs.core.next(arglist__6876));
return G__6872__delegate(x, y, more);
});
G__6872.cljs$lang$arity$variadic = G__6872__delegate;
return G__6872;
})()
;
_EQ_ = function(x,y,var_args){
var more = var_args;
switch(arguments.length){
case 1:
return _EQ___1.call(this,x);
case 2:
return _EQ___2.call(this,x,y);
default:
return _EQ___3.cljs$lang$arity$variadic(x,y, cljs.core.array_seq(arguments, 2));
}
throw('Invalid arity: ' + arguments.length);
};
_EQ_.cljs$lang$maxFixedArity = 2;
_EQ_.cljs$lang$applyTo = _EQ___3.cljs$lang$applyTo;
_EQ_.cljs$lang$arity$1 = _EQ___1;
_EQ_.cljs$lang$arity$2 = _EQ___2;
_EQ_.cljs$lang$arity$variadic = _EQ___3.cljs$lang$arity$variadic;
return _EQ_;
})()
;
/**
* Returns true if x is nil, false otherwise.
*/
cljs.core.nil_QMARK_ = (function nil_QMARK_(x){
return (x == null);
});
cljs.core.type = (function type(x){
if((x == null))
{return null;
} else
{return x.constructor;
}
});
cljs.core.instance_QMARK_ = (function instance_QMARK_(t,o){
return (o instanceof t);
});
(cljs.core.IHash["null"] = true);
(cljs.core._hash["null"] = (function (o){
return 0;
}));
(cljs.core.ILookup["null"] = true);
(cljs.core._lookup["null"] = (function() {
var G__6877 = null;
var G__6877__2 = (function (o,k){
return null;
});
var G__6877__3 = (function (o,k,not_found){
return not_found;
});
G__6877 = function(o,k,not_found){
switch(arguments.length){
case 2:
return G__6877__2.call(this,o,k);
case 3:
return G__6877__3.call(this,o,k,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
return G__6877;
})()
);
(cljs.core.IAssociative["null"] = true);
(cljs.core._assoc["null"] = (function (_,k,v){
return cljs.core.hash_map.call(null,k,v);
}));
(cljs.core.INext["null"] = true);
(cljs.core._next["null"] = (function (_){
return null;
}));
(cljs.core.ICollection["null"] = true);
(cljs.core._conj["null"] = (function (_,o){
return cljs.core.list.call(null,o);
}));
(cljs.core.IReduce["null"] = true);
(cljs.core._reduce["null"] = (function() {
var G__6878 = null;
var G__6878__2 = (function (_,f){
return f.call(null);
});
var G__6878__3 = (function (_,f,start){
return start;
});
G__6878 = function(_,f,start){
switch(arguments.length){
case 2:
return G__6878__2.call(this,_,f);
case 3:
return G__6878__3.call(this,_,f,start);
}
throw('Invalid arity: ' + arguments.length);
};
return G__6878;
})()
);
(cljs.core.IPrintable["null"] = true);
(cljs.core._pr_seq["null"] = (function (o){
return cljs.core.list.call(null,"nil");
}));
(cljs.core.ISet["null"] = true);
(cljs.core._disjoin["null"] = (function (_,v){
return null;
}));
(cljs.core.ICounted["null"] = true);
(cljs.core._count["null"] = (function (_){
return 0;
}));
(cljs.core.IStack["null"] = true);
(cljs.core._peek["null"] = (function (_){
return null;
}));
(cljs.core._pop["null"] = (function (_){
return null;
}));
(cljs.core.ISeq["null"] = true);
(cljs.core._first["null"] = (function (_){
return null;
}));
(cljs.core._rest["null"] = (function (_){
return cljs.core.list.call(null);
}));
(cljs.core.IEquiv["null"] = true);
(cljs.core._equiv["null"] = (function (_,o){
return (o == null);
}));
(cljs.core.IWithMeta["null"] = true);
(cljs.core._with_meta["null"] = (function (_,meta){
return null;
}));
(cljs.core.IMeta["null"] = true);
(cljs.core._meta["null"] = (function (_){
return null;
}));
(cljs.core.IIndexed["null"] = true);
(cljs.core._nth["null"] = (function() {
var G__6879 = null;
var G__6879__2 = (function (_,n){
return null;
});
var G__6879__3 = (function (_,n,not_found){
return not_found;
});
G__6879 = function(_,n,not_found){
switch(arguments.length){
case 2:
return G__6879__2.call(this,_,n);
case 3:
return G__6879__3.call(this,_,n,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
return G__6879;
})()
);
(cljs.core.IEmptyableCollection["null"] = true);
(cljs.core._empty["null"] = (function (_){
return null;
}));
(cljs.core.IMap["null"] = true);
(cljs.core._dissoc["null"] = (function (_,k){
return null;
}));
Date.prototype.cljs$core$IEquiv$ = true;
Date.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (o,other){
var and__3822__auto____6880 = cljs.core.instance_QMARK_.call(null,Date,other);
if(and__3822__auto____6880)
{return (o.toString() === other.toString());
} else
{return and__3822__auto____6880;
}
});
(cljs.core.IHash["number"] = true);
(cljs.core._hash["number"] = (function (o){
return o;
}));
(cljs.core.IEquiv["number"] = true);
(cljs.core._equiv["number"] = (function (x,o){
return (x === o);
}));
(cljs.core.IHash["boolean"] = true);
(cljs.core._hash["boolean"] = (function (o){
if((o === true))
{return 1;
} else
{return 0;
}
}));
(cljs.core.IHash["_"] = true);
(cljs.core._hash["_"] = (function (o){
return goog.getUid(o);
}));
/**
* Returns a number one greater than num.
*/
cljs.core.inc = (function inc(x){
return (x + 1);
});
/**
* Accepts any collection which satisfies the ICount and IIndexed protocols and
* reduces them without incurring seq initialization
*/
cljs.core.ci_reduce = (function() {
var ci_reduce = null;
var ci_reduce__2 = (function (cicoll,f){
var cnt__6893 = cljs.core._count.call(null,cicoll);
if((cnt__6893 === 0))
{return f.call(null);
} else
{var val__6894 = cljs.core._nth.call(null,cicoll,0);
var n__6895 = 1;
while(true){
if((n__6895 < cnt__6893))
{var nval__6896 = f.call(null,val__6894,cljs.core._nth.call(null,cicoll,n__6895));
if(cljs.core.reduced_QMARK_.call(null,nval__6896))
{return cljs.core.deref.call(null,nval__6896);
} else
{{
var G__6905 = nval__6896;
var G__6906 = (n__6895 + 1);
val__6894 = G__6905;
n__6895 = G__6906;
continue;
}
}
} else
{return val__6894;
}
break;
}
}
});
var ci_reduce__3 = (function (cicoll,f,val){
var cnt__6897 = cljs.core._count.call(null,cicoll);
var val__6898 = val;
var n__6899 = 0;
while(true){
if((n__6899 < cnt__6897))
{var nval__6900 = f.call(null,val__6898,cljs.core._nth.call(null,cicoll,n__6899));
if(cljs.core.reduced_QMARK_.call(null,nval__6900))
{return cljs.core.deref.call(null,nval__6900);
} else
{{
var G__6907 = nval__6900;
var G__6908 = (n__6899 + 1);
val__6898 = G__6907;
n__6899 = G__6908;
continue;
}
}
} else
{return val__6898;
}
break;
}
});
var ci_reduce__4 = (function (cicoll,f,val,idx){
var cnt__6901 = cljs.core._count.call(null,cicoll);
var val__6902 = val;
var n__6903 = idx;
while(true){
if((n__6903 < cnt__6901))
{var nval__6904 = f.call(null,val__6902,cljs.core._nth.call(null,cicoll,n__6903));
if(cljs.core.reduced_QMARK_.call(null,nval__6904))
{return cljs.core.deref.call(null,nval__6904);
} else
{{
var G__6909 = nval__6904;
var G__6910 = (n__6903 + 1);
val__6902 = G__6909;
n__6903 = G__6910;
continue;
}
}
} else
{return val__6902;
}
break;
}
});
ci_reduce = function(cicoll,f,val,idx){
switch(arguments.length){
case 2:
return ci_reduce__2.call(this,cicoll,f);
case 3:
return ci_reduce__3.call(this,cicoll,f,val);
case 4:
return ci_reduce__4.call(this,cicoll,f,val,idx);
}
throw('Invalid arity: ' + arguments.length);
};
ci_reduce.cljs$lang$arity$2 = ci_reduce__2;
ci_reduce.cljs$lang$arity$3 = ci_reduce__3;
ci_reduce.cljs$lang$arity$4 = ci_reduce__4;
return ci_reduce;
})()
;
cljs.core.array_reduce = (function() {
var array_reduce = null;
var array_reduce__2 = (function (arr,f){
var cnt__6923 = arr.length;
if((arr.length === 0))
{return f.call(null);
} else
{var val__6924 = (arr[0]);
var n__6925 = 1;
while(true){
if((n__6925 < cnt__6923))
{var nval__6926 = f.call(null,val__6924,(arr[n__6925]));
if(cljs.core.reduced_QMARK_.call(null,nval__6926))
{return cljs.core.deref.call(null,nval__6926);
} else
{{
var G__6935 = nval__6926;
var G__6936 = (n__6925 + 1);
val__6924 = G__6935;
n__6925 = G__6936;
continue;
}
}
} else
{return val__6924;
}
break;
}
}
});
var array_reduce__3 = (function (arr,f,val){
var cnt__6927 = arr.length;
var val__6928 = val;
var n__6929 = 0;
while(true){
if((n__6929 < cnt__6927))
{var nval__6930 = f.call(null,val__6928,(arr[n__6929]));
if(cljs.core.reduced_QMARK_.call(null,nval__6930))
{return cljs.core.deref.call(null,nval__6930);
} else
{{
var G__6937 = nval__6930;
var G__6938 = (n__6929 + 1);
val__6928 = G__6937;
n__6929 = G__6938;
continue;
}
}
} else
{return val__6928;
}
break;
}
});
var array_reduce__4 = (function (arr,f,val,idx){
var cnt__6931 = arr.length;
var val__6932 = val;
var n__6933 = idx;
while(true){
if((n__6933 < cnt__6931))
{var nval__6934 = f.call(null,val__6932,(arr[n__6933]));
if(cljs.core.reduced_QMARK_.call(null,nval__6934))
{return cljs.core.deref.call(null,nval__6934);
} else
{{
var G__6939 = nval__6934;
var G__6940 = (n__6933 + 1);
val__6932 = G__6939;
n__6933 = G__6940;
continue;
}
}
} else
{return val__6932;
}
break;
}
});
array_reduce = function(arr,f,val,idx){
switch(arguments.length){
case 2:
return array_reduce__2.call(this,arr,f);
case 3:
return array_reduce__3.call(this,arr,f,val);
case 4:
return array_reduce__4.call(this,arr,f,val,idx);
}
throw('Invalid arity: ' + arguments.length);
};
array_reduce.cljs$lang$arity$2 = array_reduce__2;
array_reduce.cljs$lang$arity$3 = array_reduce__3;
array_reduce.cljs$lang$arity$4 = array_reduce__4;
return array_reduce;
})()
;

/**
* @constructor
*/
cljs.core.IndexedSeq = (function (a,i){
this.a = a;
this.i = i;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 166199546;
})
cljs.core.IndexedSeq.cljs$lang$type = true;
cljs.core.IndexedSeq.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/IndexedSeq");
});
cljs.core.IndexedSeq.prototype.cljs$core$IHash$_hash$arity$1 = (function (coll){
var this__6941 = this;
return cljs.core.hash_coll.call(null,coll);
});
cljs.core.IndexedSeq.prototype.cljs$core$INext$_next$arity$1 = (function (_){
var this__6942 = this;
if(((this__6942.i + 1) < this__6942.a.length))
{return (new cljs.core.IndexedSeq(this__6942.a,(this__6942.i + 1)));
} else
{return null;
}
});
cljs.core.IndexedSeq.prototype.cljs$core$ICollection$_conj$arity$2 = (function (coll,o){
var this__6943 = this;
return cljs.core.cons.call(null,o,coll);
});
cljs.core.IndexedSeq.prototype.cljs$core$IReversible$_rseq$arity$1 = (function (coll){
var this__6944 = this;
var c__6945 = coll.cljs$core$ICounted$_count$arity$1(coll);
if((c__6945 > 0))
{return (new cljs.core.RSeq(coll,(c__6945 - 1),null));
} else
{return cljs.core.List.EMPTY;
}
});
cljs.core.IndexedSeq.prototype.toString = (function (){
var this__6946 = this;
var this__6947 = this;
return cljs.core.pr_str.call(null,this__6947);
});
cljs.core.IndexedSeq.prototype.cljs$core$IReduce$_reduce$arity$2 = (function (coll,f){
var this__6948 = this;
if(cljs.core.counted_QMARK_.call(null,this__6948.a))
{return cljs.core.ci_reduce.call(null,this__6948.a,f,(this__6948.a[this__6948.i]),(this__6948.i + 1));
} else
{return cljs.core.ci_reduce.call(null,coll,f,(this__6948.a[this__6948.i]),0);
}
});
cljs.core.IndexedSeq.prototype.cljs$core$IReduce$_reduce$arity$3 = (function (coll,f,start){
var this__6949 = this;
if(cljs.core.counted_QMARK_.call(null,this__6949.a))
{return cljs.core.ci_reduce.call(null,this__6949.a,f,start,this__6949.i);
} else
{return cljs.core.ci_reduce.call(null,coll,f,start,0);
}
});
cljs.core.IndexedSeq.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (this$){
var this__6950 = this;
return this$;
});
cljs.core.IndexedSeq.prototype.cljs$core$ICounted$_count$arity$1 = (function (_){
var this__6951 = this;
return (this__6951.a.length - this__6951.i);
});
cljs.core.IndexedSeq.prototype.cljs$core$ISeq$_first$arity$1 = (function (_){
var this__6952 = this;
return (this__6952.a[this__6952.i]);
});
cljs.core.IndexedSeq.prototype.cljs$core$ISeq$_rest$arity$1 = (function (_){
var this__6953 = this;
if(((this__6953.i + 1) < this__6953.a.length))
{return (new cljs.core.IndexedSeq(this__6953.a,(this__6953.i + 1)));
} else
{return cljs.core.list.call(null);
}
});
cljs.core.IndexedSeq.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (coll,other){
var this__6954 = this;
return cljs.core.equiv_sequential.call(null,coll,other);
});
cljs.core.IndexedSeq.prototype.cljs$core$IIndexed$_nth$arity$2 = (function (coll,n){
var this__6955 = this;
var i__6956 = (n + this__6955.i);
if((i__6956 < this__6955.a.length))
{return (this__6955.a[i__6956]);
} else
{return null;
}
});
cljs.core.IndexedSeq.prototype.cljs$core$IIndexed$_nth$arity$3 = (function (coll,n,not_found){
var this__6957 = this;
var i__6958 = (n + this__6957.i);
if((i__6958 < this__6957.a.length))
{return (this__6957.a[i__6958]);
} else
{return not_found;
}
});
cljs.core.IndexedSeq;
cljs.core.prim_seq = (function() {
var prim_seq = null;
var prim_seq__1 = (function (prim){
return prim_seq.call(null,prim,0);
});
var prim_seq__2 = (function (prim,i){
if((prim.length === 0))
{return null;
} else
{return (new cljs.core.IndexedSeq(prim,i));
}
});
prim_seq = function(prim,i){
switch(arguments.length){
case 1:
return prim_seq__1.call(this,prim);
case 2:
return prim_seq__2.call(this,prim,i);
}
throw('Invalid arity: ' + arguments.length);
};
prim_seq.cljs$lang$arity$1 = prim_seq__1;
prim_seq.cljs$lang$arity$2 = prim_seq__2;
return prim_seq;
})()
;
cljs.core.array_seq = (function() {
var array_seq = null;
var array_seq__1 = (function (array){
return cljs.core.prim_seq.call(null,array,0);
});
var array_seq__2 = (function (array,i){
return cljs.core.prim_seq.call(null,array,i);
});
array_seq = function(array,i){
switch(arguments.length){
case 1:
return array_seq__1.call(this,array);
case 2:
return array_seq__2.call(this,array,i);
}
throw('Invalid arity: ' + arguments.length);
};
array_seq.cljs$lang$arity$1 = array_seq__1;
array_seq.cljs$lang$arity$2 = array_seq__2;
return array_seq;
})()
;
(cljs.core.IReduce["array"] = true);
(cljs.core._reduce["array"] = (function() {
var G__6959 = null;
var G__6959__2 = (function (array,f){
return cljs.core.ci_reduce.call(null,array,f);
});
var G__6959__3 = (function (array,f,start){
return cljs.core.ci_reduce.call(null,array,f,start);
});
G__6959 = function(array,f,start){
switch(arguments.length){
case 2:
return G__6959__2.call(this,array,f);
case 3:
return G__6959__3.call(this,array,f,start);
}
throw('Invalid arity: ' + arguments.length);
};
return G__6959;
})()
);
(cljs.core.ILookup["array"] = true);
(cljs.core._lookup["array"] = (function() {
var G__6960 = null;
var G__6960__2 = (function (array,k){
return (array[k]);
});
var G__6960__3 = (function (array,k,not_found){
return cljs.core._nth.call(null,array,k,not_found);
});
G__6960 = function(array,k,not_found){
switch(arguments.length){
case 2:
return G__6960__2.call(this,array,k);
case 3:
return G__6960__3.call(this,array,k,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
return G__6960;
})()
);
(cljs.core.IIndexed["array"] = true);
(cljs.core._nth["array"] = (function() {
var G__6961 = null;
var G__6961__2 = (function (array,n){
if((n < array.length))
{return (array[n]);
} else
{return null;
}
});
var G__6961__3 = (function (array,n,not_found){
if((n < array.length))
{return (array[n]);
} else
{return not_found;
}
});
G__6961 = function(array,n,not_found){
switch(arguments.length){
case 2:
return G__6961__2.call(this,array,n);
case 3:
return G__6961__3.call(this,array,n,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
return G__6961;
})()
);
(cljs.core.ICounted["array"] = true);
(cljs.core._count["array"] = (function (a){
return a.length;
}));
(cljs.core.ISeqable["array"] = true);
(cljs.core._seq["array"] = (function (array){
return cljs.core.array_seq.call(null,array,0);
}));

/**
* @constructor
*/
cljs.core.RSeq = (function (ci,i,meta){
this.ci = ci;
this.i = i;
this.meta = meta;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 31850570;
})
cljs.core.RSeq.cljs$lang$type = true;
cljs.core.RSeq.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/RSeq");
});
cljs.core.RSeq.prototype.cljs$core$IHash$_hash$arity$1 = (function (coll){
var this__6962 = this;
return cljs.core.hash_coll.call(null,coll);
});
cljs.core.RSeq.prototype.cljs$core$ICollection$_conj$arity$2 = (function (coll,o){
var this__6963 = this;
return cljs.core.cons.call(null,o,coll);
});
cljs.core.RSeq.prototype.toString = (function (){
var this__6964 = this;
var this__6965 = this;
return cljs.core.pr_str.call(null,this__6965);
});
cljs.core.RSeq.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (coll){
var this__6966 = this;
return coll;
});
cljs.core.RSeq.prototype.cljs$core$ICounted$_count$arity$1 = (function (coll){
var this__6967 = this;
return (this__6967.i + 1);
});
cljs.core.RSeq.prototype.cljs$core$ISeq$_first$arity$1 = (function (coll){
var this__6968 = this;
return cljs.core._nth.call(null,this__6968.ci,this__6968.i);
});
cljs.core.RSeq.prototype.cljs$core$ISeq$_rest$arity$1 = (function (coll){
var this__6969 = this;
if((this__6969.i > 0))
{return (new cljs.core.RSeq(this__6969.ci,(this__6969.i - 1),null));
} else
{return cljs.core.List.EMPTY;
}
});
cljs.core.RSeq.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (coll,other){
var this__6970 = this;
return cljs.core.equiv_sequential.call(null,coll,other);
});
cljs.core.RSeq.prototype.cljs$core$IWithMeta$_with_meta$arity$2 = (function (coll,new_meta){
var this__6971 = this;
return (new cljs.core.RSeq(this__6971.ci,this__6971.i,new_meta));
});
cljs.core.RSeq.prototype.cljs$core$IMeta$_meta$arity$1 = (function (coll){
var this__6972 = this;
return this__6972.meta;
});
cljs.core.RSeq;
/**
* Returns a seq on the collection. If the collection is
* empty, returns nil.  (seq nil) returns nil. seq also works on
* Strings.
*/
cljs.core.seq = (function seq(coll){
if((coll == null))
{return null;
} else
{if((function (){var G__6976__6977 = coll;
if(G__6976__6977)
{if((function (){var or__3824__auto____6978 = (G__6976__6977.cljs$lang$protocol_mask$partition0$ & 32);
if(or__3824__auto____6978)
{return or__3824__auto____6978;
} else
{return G__6976__6977.cljs$core$ASeq$;
}
})())
{return true;
} else
{if((!G__6976__6977.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.ASeq,G__6976__6977);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.ASeq,G__6976__6977);
}
})())
{return coll;
} else
{return cljs.core._seq.call(null,coll);
}
}
});
/**
* Returns the first item in the collection. Calls seq on its
* argument. If coll is nil, returns nil.
*/
cljs.core.first = (function first(coll){
if((coll == null))
{return null;
} else
{if((function (){var G__6983__6984 = coll;
if(G__6983__6984)
{if((function (){var or__3824__auto____6985 = (G__6983__6984.cljs$lang$protocol_mask$partition0$ & 64);
if(or__3824__auto____6985)
{return or__3824__auto____6985;
} else
{return G__6983__6984.cljs$core$ISeq$;
}
})())
{return true;
} else
{if((!G__6983__6984.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.ISeq,G__6983__6984);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.ISeq,G__6983__6984);
}
})())
{return cljs.core._first.call(null,coll);
} else
{var s__6986 = cljs.core.seq.call(null,coll);
if((s__6986 == null))
{return null;
} else
{return cljs.core._first.call(null,s__6986);
}
}
}
});
/**
* Returns a possibly empty seq of the items after the first. Calls seq on its
* argument.
*/
cljs.core.rest = (function rest(coll){
if(!((coll == null)))
{if((function (){var G__6991__6992 = coll;
if(G__6991__6992)
{if((function (){var or__3824__auto____6993 = (G__6991__6992.cljs$lang$protocol_mask$partition0$ & 64);
if(or__3824__auto____6993)
{return or__3824__auto____6993;
} else
{return G__6991__6992.cljs$core$ISeq$;
}
})())
{return true;
} else
{if((!G__6991__6992.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.ISeq,G__6991__6992);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.ISeq,G__6991__6992);
}
})())
{return cljs.core._rest.call(null,coll);
} else
{var s__6994 = cljs.core.seq.call(null,coll);
if(!((s__6994 == null)))
{return cljs.core._rest.call(null,s__6994);
} else
{return cljs.core.List.EMPTY;
}
}
} else
{return cljs.core.List.EMPTY;
}
});
/**
* Returns a seq of the items after the first. Calls seq on its
* argument.  If there are no more items, returns nil
*/
cljs.core.next = (function next(coll){
if((coll == null))
{return null;
} else
{if((function (){var G__6998__6999 = coll;
if(G__6998__6999)
{if((function (){var or__3824__auto____7000 = (G__6998__6999.cljs$lang$protocol_mask$partition0$ & 128);
if(or__3824__auto____7000)
{return or__3824__auto____7000;
} else
{return G__6998__6999.cljs$core$INext$;
}
})())
{return true;
} else
{if((!G__6998__6999.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.INext,G__6998__6999);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.INext,G__6998__6999);
}
})())
{return cljs.core._next.call(null,coll);
} else
{return cljs.core.seq.call(null,cljs.core.rest.call(null,coll));
}
}
});
/**
* Same as (first (next x))
*/
cljs.core.second = (function second(coll){
return cljs.core.first.call(null,cljs.core.next.call(null,coll));
});
/**
* Same as (first (first x))
*/
cljs.core.ffirst = (function ffirst(coll){
return cljs.core.first.call(null,cljs.core.first.call(null,coll));
});
/**
* Same as (next (first x))
*/
cljs.core.nfirst = (function nfirst(coll){
return cljs.core.next.call(null,cljs.core.first.call(null,coll));
});
/**
* Same as (first (next x))
*/
cljs.core.fnext = (function fnext(coll){
return cljs.core.first.call(null,cljs.core.next.call(null,coll));
});
/**
* Same as (next (next x))
*/
cljs.core.nnext = (function nnext(coll){
return cljs.core.next.call(null,cljs.core.next.call(null,coll));
});
/**
* Return the last item in coll, in linear time
*/
cljs.core.last = (function last(s){
while(true){
var sn__7002 = cljs.core.next.call(null,s);
if(!((sn__7002 == null)))
{{
var G__7003 = sn__7002;
s = G__7003;
continue;
}
} else
{return cljs.core.first.call(null,s);
}
break;
}
});
(cljs.core.IEquiv["_"] = true);
(cljs.core._equiv["_"] = (function (x,o){
return (x === o);
}));
/**
* Returns true if x is logical false, false otherwise.
*/
cljs.core.not = (function not(x){
if(cljs.core.truth_(x))
{return false;
} else
{return true;
}
});
/**
* conj[oin]. Returns a new collection with the xs
* 'added'. (conj nil item) returns (item).  The 'addition' may
* happen at different 'places' depending on the concrete type.
* @param {...*} var_args
*/
cljs.core.conj = (function() {
var conj = null;
var conj__2 = (function (coll,x){
return cljs.core._conj.call(null,coll,x);
});
var conj__3 = (function() { 
var G__7004__delegate = function (coll,x,xs){
while(true){
if(cljs.core.truth_(xs))
{{
var G__7005 = conj.call(null,coll,x);
var G__7006 = cljs.core.first.call(null,xs);
var G__7007 = cljs.core.next.call(null,xs);
coll = G__7005;
x = G__7006;
xs = G__7007;
continue;
}
} else
{return conj.call(null,coll,x);
}
break;
}
};
var G__7004 = function (coll,x,var_args){
var xs = null;
if (goog.isDef(var_args)) {
  xs = cljs.core.array_seq(Array.prototype.slice.call(arguments, 2),0);
} 
return G__7004__delegate.call(this, coll, x, xs);
};
G__7004.cljs$lang$maxFixedArity = 2;
G__7004.cljs$lang$applyTo = (function (arglist__7008){
var coll = cljs.core.first(arglist__7008);
var x = cljs.core.first(cljs.core.next(arglist__7008));
var xs = cljs.core.rest(cljs.core.next(arglist__7008));
return G__7004__delegate(coll, x, xs);
});
G__7004.cljs$lang$arity$variadic = G__7004__delegate;
return G__7004;
})()
;
conj = function(coll,x,var_args){
var xs = var_args;
switch(arguments.length){
case 2:
return conj__2.call(this,coll,x);
default:
return conj__3.cljs$lang$arity$variadic(coll,x, cljs.core.array_seq(arguments, 2));
}
throw('Invalid arity: ' + arguments.length);
};
conj.cljs$lang$maxFixedArity = 2;
conj.cljs$lang$applyTo = conj__3.cljs$lang$applyTo;
conj.cljs$lang$arity$2 = conj__2;
conj.cljs$lang$arity$variadic = conj__3.cljs$lang$arity$variadic;
return conj;
})()
;
/**
* Returns an empty collection of the same category as coll, or nil
*/
cljs.core.empty = (function empty(coll){
return cljs.core._empty.call(null,coll);
});
cljs.core.accumulating_seq_count = (function accumulating_seq_count(coll){
var s__7011 = cljs.core.seq.call(null,coll);
var acc__7012 = 0;
while(true){
if(cljs.core.counted_QMARK_.call(null,s__7011))
{return (acc__7012 + cljs.core._count.call(null,s__7011));
} else
{{
var G__7013 = cljs.core.next.call(null,s__7011);
var G__7014 = (acc__7012 + 1);
s__7011 = G__7013;
acc__7012 = G__7014;
continue;
}
}
break;
}
});
/**
* Returns the number of items in the collection. (count nil) returns
* 0.  Also works on strings, arrays, and Maps
*/
cljs.core.count = (function count(coll){
if(cljs.core.counted_QMARK_.call(null,coll))
{return cljs.core._count.call(null,coll);
} else
{return cljs.core.accumulating_seq_count.call(null,coll);
}
});
cljs.core.linear_traversal_nth = (function() {
var linear_traversal_nth = null;
var linear_traversal_nth__2 = (function (coll,n){
if((coll == null))
{throw (new Error("Index out of bounds"));
} else
{if((n === 0))
{if(cljs.core.seq.call(null,coll))
{return cljs.core.first.call(null,coll);
} else
{throw (new Error("Index out of bounds"));
}
} else
{if(cljs.core.indexed_QMARK_.call(null,coll))
{return cljs.core._nth.call(null,coll,n);
} else
{if(cljs.core.seq.call(null,coll))
{return linear_traversal_nth.call(null,cljs.core.next.call(null,coll),(n - 1));
} else
{if("\uFDD0'else")
{throw (new Error("Index out of bounds"));
} else
{return null;
}
}
}
}
}
});
var linear_traversal_nth__3 = (function (coll,n,not_found){
if((coll == null))
{return not_found;
} else
{if((n === 0))
{if(cljs.core.seq.call(null,coll))
{return cljs.core.first.call(null,coll);
} else
{return not_found;
}
} else
{if(cljs.core.indexed_QMARK_.call(null,coll))
{return cljs.core._nth.call(null,coll,n,not_found);
} else
{if(cljs.core.seq.call(null,coll))
{return linear_traversal_nth.call(null,cljs.core.next.call(null,coll),(n - 1),not_found);
} else
{if("\uFDD0'else")
{return not_found;
} else
{return null;
}
}
}
}
}
});
linear_traversal_nth = function(coll,n,not_found){
switch(arguments.length){
case 2:
return linear_traversal_nth__2.call(this,coll,n);
case 3:
return linear_traversal_nth__3.call(this,coll,n,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
linear_traversal_nth.cljs$lang$arity$2 = linear_traversal_nth__2;
linear_traversal_nth.cljs$lang$arity$3 = linear_traversal_nth__3;
return linear_traversal_nth;
})()
;
/**
* Returns the value at the index. get returns nil if index out of
* bounds, nth throws an exception unless not-found is supplied.  nth
* also works for strings, arrays, regex Matchers and Lists, and,
* in O(n) time, for sequences.
*/
cljs.core.nth = (function() {
var nth = null;
var nth__2 = (function (coll,n){
if((coll == null))
{return null;
} else
{if((function (){var G__7021__7022 = coll;
if(G__7021__7022)
{if((function (){var or__3824__auto____7023 = (G__7021__7022.cljs$lang$protocol_mask$partition0$ & 16);
if(or__3824__auto____7023)
{return or__3824__auto____7023;
} else
{return G__7021__7022.cljs$core$IIndexed$;
}
})())
{return true;
} else
{if((!G__7021__7022.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.IIndexed,G__7021__7022);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.IIndexed,G__7021__7022);
}
})())
{return cljs.core._nth.call(null,coll,Math.floor(n));
} else
{return cljs.core.linear_traversal_nth.call(null,coll,Math.floor(n));
}
}
});
var nth__3 = (function (coll,n,not_found){
if(!((coll == null)))
{if((function (){var G__7024__7025 = coll;
if(G__7024__7025)
{if((function (){var or__3824__auto____7026 = (G__7024__7025.cljs$lang$protocol_mask$partition0$ & 16);
if(or__3824__auto____7026)
{return or__3824__auto____7026;
} else
{return G__7024__7025.cljs$core$IIndexed$;
}
})())
{return true;
} else
{if((!G__7024__7025.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.IIndexed,G__7024__7025);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.IIndexed,G__7024__7025);
}
})())
{return cljs.core._nth.call(null,coll,Math.floor(n),not_found);
} else
{return cljs.core.linear_traversal_nth.call(null,coll,Math.floor(n),not_found);
}
} else
{return not_found;
}
});
nth = function(coll,n,not_found){
switch(arguments.length){
case 2:
return nth__2.call(this,coll,n);
case 3:
return nth__3.call(this,coll,n,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
nth.cljs$lang$arity$2 = nth__2;
nth.cljs$lang$arity$3 = nth__3;
return nth;
})()
;
/**
* Returns the value mapped to key, not-found or nil if key not present.
*/
cljs.core.get = (function() {
var get = null;
var get__2 = (function (o,k){
return cljs.core._lookup.call(null,o,k);
});
var get__3 = (function (o,k,not_found){
return cljs.core._lookup.call(null,o,k,not_found);
});
get = function(o,k,not_found){
switch(arguments.length){
case 2:
return get__2.call(this,o,k);
case 3:
return get__3.call(this,o,k,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
get.cljs$lang$arity$2 = get__2;
get.cljs$lang$arity$3 = get__3;
return get;
})()
;
/**
* assoc[iate]. When applied to a map, returns a new map of the
* same (hashed/sorted) type, that contains the mapping of key(s) to
* val(s). When applied to a vector, returns a new vector that
* contains val at index.
* @param {...*} var_args
*/
cljs.core.assoc = (function() {
var assoc = null;
var assoc__3 = (function (coll,k,v){
return cljs.core._assoc.call(null,coll,k,v);
});
var assoc__4 = (function() { 
var G__7029__delegate = function (coll,k,v,kvs){
while(true){
var ret__7028 = assoc.call(null,coll,k,v);
if(cljs.core.truth_(kvs))
{{
var G__7030 = ret__7028;
var G__7031 = cljs.core.first.call(null,kvs);
var G__7032 = cljs.core.second.call(null,kvs);
var G__7033 = cljs.core.nnext.call(null,kvs);
coll = G__7030;
k = G__7031;
v = G__7032;
kvs = G__7033;
continue;
}
} else
{return ret__7028;
}
break;
}
};
var G__7029 = function (coll,k,v,var_args){
var kvs = null;
if (goog.isDef(var_args)) {
  kvs = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return G__7029__delegate.call(this, coll, k, v, kvs);
};
G__7029.cljs$lang$maxFixedArity = 3;
G__7029.cljs$lang$applyTo = (function (arglist__7034){
var coll = cljs.core.first(arglist__7034);
var k = cljs.core.first(cljs.core.next(arglist__7034));
var v = cljs.core.first(cljs.core.next(cljs.core.next(arglist__7034)));
var kvs = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__7034)));
return G__7029__delegate(coll, k, v, kvs);
});
G__7029.cljs$lang$arity$variadic = G__7029__delegate;
return G__7029;
})()
;
assoc = function(coll,k,v,var_args){
var kvs = var_args;
switch(arguments.length){
case 3:
return assoc__3.call(this,coll,k,v);
default:
return assoc__4.cljs$lang$arity$variadic(coll,k,v, cljs.core.array_seq(arguments, 3));
}
throw('Invalid arity: ' + arguments.length);
};
assoc.cljs$lang$maxFixedArity = 3;
assoc.cljs$lang$applyTo = assoc__4.cljs$lang$applyTo;
assoc.cljs$lang$arity$3 = assoc__3;
assoc.cljs$lang$arity$variadic = assoc__4.cljs$lang$arity$variadic;
return assoc;
})()
;
/**
* dissoc[iate]. Returns a new map of the same (hashed/sorted) type,
* that does not contain a mapping for key(s).
* @param {...*} var_args
*/
cljs.core.dissoc = (function() {
var dissoc = null;
var dissoc__1 = (function (coll){
return coll;
});
var dissoc__2 = (function (coll,k){
return cljs.core._dissoc.call(null,coll,k);
});
var dissoc__3 = (function() { 
var G__7037__delegate = function (coll,k,ks){
while(true){
var ret__7036 = dissoc.call(null,coll,k);
if(cljs.core.truth_(ks))
{{
var G__7038 = ret__7036;
var G__7039 = cljs.core.first.call(null,ks);
var G__7040 = cljs.core.next.call(null,ks);
coll = G__7038;
k = G__7039;
ks = G__7040;
continue;
}
} else
{return ret__7036;
}
break;
}
};
var G__7037 = function (coll,k,var_args){
var ks = null;
if (goog.isDef(var_args)) {
  ks = cljs.core.array_seq(Array.prototype.slice.call(arguments, 2),0);
} 
return G__7037__delegate.call(this, coll, k, ks);
};
G__7037.cljs$lang$maxFixedArity = 2;
G__7037.cljs$lang$applyTo = (function (arglist__7041){
var coll = cljs.core.first(arglist__7041);
var k = cljs.core.first(cljs.core.next(arglist__7041));
var ks = cljs.core.rest(cljs.core.next(arglist__7041));
return G__7037__delegate(coll, k, ks);
});
G__7037.cljs$lang$arity$variadic = G__7037__delegate;
return G__7037;
})()
;
dissoc = function(coll,k,var_args){
var ks = var_args;
switch(arguments.length){
case 1:
return dissoc__1.call(this,coll);
case 2:
return dissoc__2.call(this,coll,k);
default:
return dissoc__3.cljs$lang$arity$variadic(coll,k, cljs.core.array_seq(arguments, 2));
}
throw('Invalid arity: ' + arguments.length);
};
dissoc.cljs$lang$maxFixedArity = 2;
dissoc.cljs$lang$applyTo = dissoc__3.cljs$lang$applyTo;
dissoc.cljs$lang$arity$1 = dissoc__1;
dissoc.cljs$lang$arity$2 = dissoc__2;
dissoc.cljs$lang$arity$variadic = dissoc__3.cljs$lang$arity$variadic;
return dissoc;
})()
;
/**
* Returns an object of the same type and value as obj, with
* map m as its metadata.
*/
cljs.core.with_meta = (function with_meta(o,meta){
return cljs.core._with_meta.call(null,o,meta);
});
/**
* Returns the metadata of obj, returns nil if there is no metadata.
*/
cljs.core.meta = (function meta(o){
if((function (){var G__7045__7046 = o;
if(G__7045__7046)
{if((function (){var or__3824__auto____7047 = (G__7045__7046.cljs$lang$protocol_mask$partition0$ & 131072);
if(or__3824__auto____7047)
{return or__3824__auto____7047;
} else
{return G__7045__7046.cljs$core$IMeta$;
}
})())
{return true;
} else
{if((!G__7045__7046.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.IMeta,G__7045__7046);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.IMeta,G__7045__7046);
}
})())
{return cljs.core._meta.call(null,o);
} else
{return null;
}
});
/**
* For a list or queue, same as first, for a vector, same as, but much
* more efficient than, last. If the collection is empty, returns nil.
*/
cljs.core.peek = (function peek(coll){
return cljs.core._peek.call(null,coll);
});
/**
* For a list or queue, returns a new list/queue without the first
* item, for a vector, returns a new vector without the last item.
* Note - not the same as next/butlast.
*/
cljs.core.pop = (function pop(coll){
return cljs.core._pop.call(null,coll);
});
/**
* disj[oin]. Returns a new set of the same (hashed/sorted) type, that
* does not contain key(s).
* @param {...*} var_args
*/
cljs.core.disj = (function() {
var disj = null;
var disj__1 = (function (coll){
return coll;
});
var disj__2 = (function (coll,k){
return cljs.core._disjoin.call(null,coll,k);
});
var disj__3 = (function() { 
var G__7050__delegate = function (coll,k,ks){
while(true){
var ret__7049 = disj.call(null,coll,k);
if(cljs.core.truth_(ks))
{{
var G__7051 = ret__7049;
var G__7052 = cljs.core.first.call(null,ks);
var G__7053 = cljs.core.next.call(null,ks);
coll = G__7051;
k = G__7052;
ks = G__7053;
continue;
}
} else
{return ret__7049;
}
break;
}
};
var G__7050 = function (coll,k,var_args){
var ks = null;
if (goog.isDef(var_args)) {
  ks = cljs.core.array_seq(Array.prototype.slice.call(arguments, 2),0);
} 
return G__7050__delegate.call(this, coll, k, ks);
};
G__7050.cljs$lang$maxFixedArity = 2;
G__7050.cljs$lang$applyTo = (function (arglist__7054){
var coll = cljs.core.first(arglist__7054);
var k = cljs.core.first(cljs.core.next(arglist__7054));
var ks = cljs.core.rest(cljs.core.next(arglist__7054));
return G__7050__delegate(coll, k, ks);
});
G__7050.cljs$lang$arity$variadic = G__7050__delegate;
return G__7050;
})()
;
disj = function(coll,k,var_args){
var ks = var_args;
switch(arguments.length){
case 1:
return disj__1.call(this,coll);
case 2:
return disj__2.call(this,coll,k);
default:
return disj__3.cljs$lang$arity$variadic(coll,k, cljs.core.array_seq(arguments, 2));
}
throw('Invalid arity: ' + arguments.length);
};
disj.cljs$lang$maxFixedArity = 2;
disj.cljs$lang$applyTo = disj__3.cljs$lang$applyTo;
disj.cljs$lang$arity$1 = disj__1;
disj.cljs$lang$arity$2 = disj__2;
disj.cljs$lang$arity$variadic = disj__3.cljs$lang$arity$variadic;
return disj;
})()
;
cljs.core.string_hash_cache = {};
cljs.core.string_hash_cache_count = 0;
cljs.core.add_to_string_hash_cache = (function add_to_string_hash_cache(k){
var h__7056 = goog.string.hashCode(k);
(cljs.core.string_hash_cache[k] = h__7056);
cljs.core.string_hash_cache_count = (cljs.core.string_hash_cache_count + 1);
return h__7056;
});
cljs.core.check_string_hash_cache = (function check_string_hash_cache(k){
if((cljs.core.string_hash_cache_count > 255))
{cljs.core.string_hash_cache = {};
cljs.core.string_hash_cache_count = 0;
} else
{}
var h__7058 = (cljs.core.string_hash_cache[k]);
if(!((h__7058 == null)))
{return h__7058;
} else
{return cljs.core.add_to_string_hash_cache.call(null,k);
}
});
cljs.core.hash = (function() {
var hash = null;
var hash__1 = (function (o){
return hash.call(null,o,true);
});
var hash__2 = (function (o,check_cache){
if((function (){var and__3822__auto____7060 = goog.isString(o);
if(and__3822__auto____7060)
{return check_cache;
} else
{return and__3822__auto____7060;
}
})())
{return cljs.core.check_string_hash_cache.call(null,o);
} else
{return cljs.core._hash.call(null,o);
}
});
hash = function(o,check_cache){
switch(arguments.length){
case 1:
return hash__1.call(this,o);
case 2:
return hash__2.call(this,o,check_cache);
}
throw('Invalid arity: ' + arguments.length);
};
hash.cljs$lang$arity$1 = hash__1;
hash.cljs$lang$arity$2 = hash__2;
return hash;
})()
;
/**
* Returns true if coll has no items - same as (not (seq coll)).
* Please use the idiom (seq x) rather than (not (empty? x))
*/
cljs.core.empty_QMARK_ = (function empty_QMARK_(coll){
return cljs.core.not.call(null,cljs.core.seq.call(null,coll));
});
/**
* Returns true if x satisfies ICollection
*/
cljs.core.coll_QMARK_ = (function coll_QMARK_(x){
if((x == null))
{return false;
} else
{var G__7064__7065 = x;
if(G__7064__7065)
{if((function (){var or__3824__auto____7066 = (G__7064__7065.cljs$lang$protocol_mask$partition0$ & 8);
if(or__3824__auto____7066)
{return or__3824__auto____7066;
} else
{return G__7064__7065.cljs$core$ICollection$;
}
})())
{return true;
} else
{if((!G__7064__7065.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.ICollection,G__7064__7065);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.ICollection,G__7064__7065);
}
}
});
/**
* Returns true if x satisfies ISet
*/
cljs.core.set_QMARK_ = (function set_QMARK_(x){
if((x == null))
{return false;
} else
{var G__7070__7071 = x;
if(G__7070__7071)
{if((function (){var or__3824__auto____7072 = (G__7070__7071.cljs$lang$protocol_mask$partition0$ & 4096);
if(or__3824__auto____7072)
{return or__3824__auto____7072;
} else
{return G__7070__7071.cljs$core$ISet$;
}
})())
{return true;
} else
{if((!G__7070__7071.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.ISet,G__7070__7071);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.ISet,G__7070__7071);
}
}
});
/**
* Returns true if coll implements Associative
*/
cljs.core.associative_QMARK_ = (function associative_QMARK_(x){
var G__7076__7077 = x;
if(G__7076__7077)
{if((function (){var or__3824__auto____7078 = (G__7076__7077.cljs$lang$protocol_mask$partition0$ & 512);
if(or__3824__auto____7078)
{return or__3824__auto____7078;
} else
{return G__7076__7077.cljs$core$IAssociative$;
}
})())
{return true;
} else
{if((!G__7076__7077.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.IAssociative,G__7076__7077);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.IAssociative,G__7076__7077);
}
});
/**
* Returns true if coll satisfies ISequential
*/
cljs.core.sequential_QMARK_ = (function sequential_QMARK_(x){
var G__7082__7083 = x;
if(G__7082__7083)
{if((function (){var or__3824__auto____7084 = (G__7082__7083.cljs$lang$protocol_mask$partition0$ & 16777216);
if(or__3824__auto____7084)
{return or__3824__auto____7084;
} else
{return G__7082__7083.cljs$core$ISequential$;
}
})())
{return true;
} else
{if((!G__7082__7083.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.ISequential,G__7082__7083);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.ISequential,G__7082__7083);
}
});
/**
* Returns true if coll implements count in constant time
*/
cljs.core.counted_QMARK_ = (function counted_QMARK_(x){
var G__7088__7089 = x;
if(G__7088__7089)
{if((function (){var or__3824__auto____7090 = (G__7088__7089.cljs$lang$protocol_mask$partition0$ & 2);
if(or__3824__auto____7090)
{return or__3824__auto____7090;
} else
{return G__7088__7089.cljs$core$ICounted$;
}
})())
{return true;
} else
{if((!G__7088__7089.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.ICounted,G__7088__7089);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.ICounted,G__7088__7089);
}
});
/**
* Returns true if coll implements nth in constant time
*/
cljs.core.indexed_QMARK_ = (function indexed_QMARK_(x){
var G__7094__7095 = x;
if(G__7094__7095)
{if((function (){var or__3824__auto____7096 = (G__7094__7095.cljs$lang$protocol_mask$partition0$ & 16);
if(or__3824__auto____7096)
{return or__3824__auto____7096;
} else
{return G__7094__7095.cljs$core$IIndexed$;
}
})())
{return true;
} else
{if((!G__7094__7095.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.IIndexed,G__7094__7095);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.IIndexed,G__7094__7095);
}
});
/**
* Returns true if coll satisfies IReduce
*/
cljs.core.reduceable_QMARK_ = (function reduceable_QMARK_(x){
var G__7100__7101 = x;
if(G__7100__7101)
{if((function (){var or__3824__auto____7102 = (G__7100__7101.cljs$lang$protocol_mask$partition0$ & 524288);
if(or__3824__auto____7102)
{return or__3824__auto____7102;
} else
{return G__7100__7101.cljs$core$IReduce$;
}
})())
{return true;
} else
{if((!G__7100__7101.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.IReduce,G__7100__7101);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.IReduce,G__7100__7101);
}
});
/**
* Return true if x satisfies IMap
*/
cljs.core.map_QMARK_ = (function map_QMARK_(x){
if((x == null))
{return false;
} else
{var G__7106__7107 = x;
if(G__7106__7107)
{if((function (){var or__3824__auto____7108 = (G__7106__7107.cljs$lang$protocol_mask$partition0$ & 1024);
if(or__3824__auto____7108)
{return or__3824__auto____7108;
} else
{return G__7106__7107.cljs$core$IMap$;
}
})())
{return true;
} else
{if((!G__7106__7107.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.IMap,G__7106__7107);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.IMap,G__7106__7107);
}
}
});
/**
* Return true if x satisfies IVector
*/
cljs.core.vector_QMARK_ = (function vector_QMARK_(x){
var G__7112__7113 = x;
if(G__7112__7113)
{if((function (){var or__3824__auto____7114 = (G__7112__7113.cljs$lang$protocol_mask$partition0$ & 16384);
if(or__3824__auto____7114)
{return or__3824__auto____7114;
} else
{return G__7112__7113.cljs$core$IVector$;
}
})())
{return true;
} else
{if((!G__7112__7113.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.IVector,G__7112__7113);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.IVector,G__7112__7113);
}
});
cljs.core.chunked_seq_QMARK_ = (function chunked_seq_QMARK_(x){
var G__7118__7119 = x;
if(G__7118__7119)
{if(cljs.core.truth_((function (){var or__3824__auto____7120 = null;
if(cljs.core.truth_(or__3824__auto____7120))
{return or__3824__auto____7120;
} else
{return G__7118__7119.cljs$core$IChunkedSeq$;
}
})()))
{return true;
} else
{if((!G__7118__7119.cljs$lang$protocol_mask$partition$))
{return cljs.core.type_satisfies_.call(null,cljs.core.IChunkedSeq,G__7118__7119);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.IChunkedSeq,G__7118__7119);
}
});
/**
* @param {...*} var_args
*/
cljs.core.js_obj = (function() {
var js_obj = null;
var js_obj__0 = (function (){
return {};
});
var js_obj__1 = (function() { 
var G__7121__delegate = function (keyvals){
return cljs.core.apply.call(null,goog.object.create,keyvals);
};
var G__7121 = function (var_args){
var keyvals = null;
if (goog.isDef(var_args)) {
  keyvals = cljs.core.array_seq(Array.prototype.slice.call(arguments, 0),0);
} 
return G__7121__delegate.call(this, keyvals);
};
G__7121.cljs$lang$maxFixedArity = 0;
G__7121.cljs$lang$applyTo = (function (arglist__7122){
var keyvals = cljs.core.seq(arglist__7122);;
return G__7121__delegate(keyvals);
});
G__7121.cljs$lang$arity$variadic = G__7121__delegate;
return G__7121;
})()
;
js_obj = function(var_args){
var keyvals = var_args;
switch(arguments.length){
case 0:
return js_obj__0.call(this);
default:
return js_obj__1.cljs$lang$arity$variadic(cljs.core.array_seq(arguments, 0));
}
throw('Invalid arity: ' + arguments.length);
};
js_obj.cljs$lang$maxFixedArity = 0;
js_obj.cljs$lang$applyTo = js_obj__1.cljs$lang$applyTo;
js_obj.cljs$lang$arity$0 = js_obj__0;
js_obj.cljs$lang$arity$variadic = js_obj__1.cljs$lang$arity$variadic;
return js_obj;
})()
;
cljs.core.js_keys = (function js_keys(obj){
var keys__7124 = [];
goog.object.forEach(obj,(function (val,key,obj){
return keys__7124.push(key);
}));
return keys__7124;
});
cljs.core.js_delete = (function js_delete(obj,key){
return delete obj[key];
});
cljs.core.array_copy = (function array_copy(from,i,to,j,len){
var i__7128 = i;
var j__7129 = j;
var len__7130 = len;
while(true){
if((len__7130 === 0))
{return to;
} else
{(to[j__7129] = (from[i__7128]));
{
var G__7131 = (i__7128 + 1);
var G__7132 = (j__7129 + 1);
var G__7133 = (len__7130 - 1);
i__7128 = G__7131;
j__7129 = G__7132;
len__7130 = G__7133;
continue;
}
}
break;
}
});
cljs.core.array_copy_downward = (function array_copy_downward(from,i,to,j,len){
var i__7137 = (i + (len - 1));
var j__7138 = (j + (len - 1));
var len__7139 = len;
while(true){
if((len__7139 === 0))
{return to;
} else
{(to[j__7138] = (from[i__7137]));
{
var G__7140 = (i__7137 - 1);
var G__7141 = (j__7138 - 1);
var G__7142 = (len__7139 - 1);
i__7137 = G__7140;
j__7138 = G__7141;
len__7139 = G__7142;
continue;
}
}
break;
}
});
cljs.core.lookup_sentinel = {};
/**
* Returns true if x is the value false, false otherwise.
*/
cljs.core.false_QMARK_ = (function false_QMARK_(x){
return x === false;
});
/**
* Returns true if x is the value true, false otherwise.
*/
cljs.core.true_QMARK_ = (function true_QMARK_(x){
return x === true;
});
cljs.core.undefined_QMARK_ = (function undefined_QMARK_(x){
return (void 0 === x);
});
/**
* Return true if s satisfies ISeq
*/
cljs.core.seq_QMARK_ = (function seq_QMARK_(s){
if((s == null))
{return false;
} else
{var G__7146__7147 = s;
if(G__7146__7147)
{if((function (){var or__3824__auto____7148 = (G__7146__7147.cljs$lang$protocol_mask$partition0$ & 64);
if(or__3824__auto____7148)
{return or__3824__auto____7148;
} else
{return G__7146__7147.cljs$core$ISeq$;
}
})())
{return true;
} else
{if((!G__7146__7147.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.ISeq,G__7146__7147);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.ISeq,G__7146__7147);
}
}
});
/**
* Return true if s satisfies ISeqable
*/
cljs.core.seqable_QMARK_ = (function seqable_QMARK_(s){
var G__7152__7153 = s;
if(G__7152__7153)
{if((function (){var or__3824__auto____7154 = (G__7152__7153.cljs$lang$protocol_mask$partition0$ & 8388608);
if(or__3824__auto____7154)
{return or__3824__auto____7154;
} else
{return G__7152__7153.cljs$core$ISeqable$;
}
})())
{return true;
} else
{if((!G__7152__7153.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.ISeqable,G__7152__7153);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.ISeqable,G__7152__7153);
}
});
cljs.core.boolean$ = (function boolean$(x){
if(cljs.core.truth_(x))
{return true;
} else
{return false;
}
});
cljs.core.string_QMARK_ = (function string_QMARK_(x){
var and__3822__auto____7157 = goog.isString(x);
if(and__3822__auto____7157)
{return !((function (){var or__3824__auto____7158 = (x.charAt(0) === "\uFDD0");
if(or__3824__auto____7158)
{return or__3824__auto____7158;
} else
{return (x.charAt(0) === "\uFDD1");
}
})());
} else
{return and__3822__auto____7157;
}
});
cljs.core.keyword_QMARK_ = (function keyword_QMARK_(x){
var and__3822__auto____7160 = goog.isString(x);
if(and__3822__auto____7160)
{return (x.charAt(0) === "\uFDD0");
} else
{return and__3822__auto____7160;
}
});
cljs.core.symbol_QMARK_ = (function symbol_QMARK_(x){
var and__3822__auto____7162 = goog.isString(x);
if(and__3822__auto____7162)
{return (x.charAt(0) === "\uFDD1");
} else
{return and__3822__auto____7162;
}
});
cljs.core.number_QMARK_ = (function number_QMARK_(n){
return goog.isNumber(n);
});
cljs.core.fn_QMARK_ = (function fn_QMARK_(f){
return goog.isFunction(f);
});
cljs.core.ifn_QMARK_ = (function ifn_QMARK_(f){
var or__3824__auto____7167 = cljs.core.fn_QMARK_.call(null,f);
if(or__3824__auto____7167)
{return or__3824__auto____7167;
} else
{var G__7168__7169 = f;
if(G__7168__7169)
{if((function (){var or__3824__auto____7170 = (G__7168__7169.cljs$lang$protocol_mask$partition0$ & 1);
if(or__3824__auto____7170)
{return or__3824__auto____7170;
} else
{return G__7168__7169.cljs$core$IFn$;
}
})())
{return true;
} else
{if((!G__7168__7169.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.IFn,G__7168__7169);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.IFn,G__7168__7169);
}
}
});
/**
* Returns true if n is an integer.  Warning: returns true on underflow condition.
*/
cljs.core.integer_QMARK_ = (function integer_QMARK_(n){
var and__3822__auto____7172 = cljs.core.number_QMARK_.call(null,n);
if(and__3822__auto____7172)
{return (n == n.toFixed());
} else
{return and__3822__auto____7172;
}
});
/**
* Returns true if key is present in the given collection, otherwise
* returns false.  Note that for numerically indexed collections like
* vectors and arrays, this tests if the numeric key is within the
* range of indexes. 'contains?' operates constant or logarithmic time;
* it will not perform a linear search for a value.  See also 'some'.
*/
cljs.core.contains_QMARK_ = (function contains_QMARK_(coll,v){
if((cljs.core._lookup.call(null,coll,v,cljs.core.lookup_sentinel) === cljs.core.lookup_sentinel))
{return false;
} else
{return true;
}
});
/**
* Returns the map entry for key, or nil if key not present.
*/
cljs.core.find = (function find(coll,k){
if(cljs.core.truth_((function (){var and__3822__auto____7175 = coll;
if(cljs.core.truth_(and__3822__auto____7175))
{var and__3822__auto____7176 = cljs.core.associative_QMARK_.call(null,coll);
if(and__3822__auto____7176)
{return cljs.core.contains_QMARK_.call(null,coll,k);
} else
{return and__3822__auto____7176;
}
} else
{return and__3822__auto____7175;
}
})()))
{return cljs.core.PersistentVector.fromArray([k,cljs.core._lookup.call(null,coll,k)], true);
} else
{return null;
}
});
/**
* Returns true if no two of the arguments are =
* @param {...*} var_args
*/
cljs.core.distinct_QMARK_ = (function() {
var distinct_QMARK_ = null;
var distinct_QMARK___1 = (function (x){
return true;
});
var distinct_QMARK___2 = (function (x,y){
return !(cljs.core._EQ_.call(null,x,y));
});
var distinct_QMARK___3 = (function() { 
var G__7185__delegate = function (x,y,more){
if(!(cljs.core._EQ_.call(null,x,y)))
{var s__7181 = cljs.core.PersistentHashSet.fromArray([y,x]);
var xs__7182 = more;
while(true){
var x__7183 = cljs.core.first.call(null,xs__7182);
var etc__7184 = cljs.core.next.call(null,xs__7182);
if(cljs.core.truth_(xs__7182))
{if(cljs.core.contains_QMARK_.call(null,s__7181,x__7183))
{return false;
} else
{{
var G__7186 = cljs.core.conj.call(null,s__7181,x__7183);
var G__7187 = etc__7184;
s__7181 = G__7186;
xs__7182 = G__7187;
continue;
}
}
} else
{return true;
}
break;
}
} else
{return false;
}
};
var G__7185 = function (x,y,var_args){
var more = null;
if (goog.isDef(var_args)) {
  more = cljs.core.array_seq(Array.prototype.slice.call(arguments, 2),0);
} 
return G__7185__delegate.call(this, x, y, more);
};
G__7185.cljs$lang$maxFixedArity = 2;
G__7185.cljs$lang$applyTo = (function (arglist__7188){
var x = cljs.core.first(arglist__7188);
var y = cljs.core.first(cljs.core.next(arglist__7188));
var more = cljs.core.rest(cljs.core.next(arglist__7188));
return G__7185__delegate(x, y, more);
});
G__7185.cljs$lang$arity$variadic = G__7185__delegate;
return G__7185;
})()
;
distinct_QMARK_ = function(x,y,var_args){
var more = var_args;
switch(arguments.length){
case 1:
return distinct_QMARK___1.call(this,x);
case 2:
return distinct_QMARK___2.call(this,x,y);
default:
return distinct_QMARK___3.cljs$lang$arity$variadic(x,y, cljs.core.array_seq(arguments, 2));
}
throw('Invalid arity: ' + arguments.length);
};
distinct_QMARK_.cljs$lang$maxFixedArity = 2;
distinct_QMARK_.cljs$lang$applyTo = distinct_QMARK___3.cljs$lang$applyTo;
distinct_QMARK_.cljs$lang$arity$1 = distinct_QMARK___1;
distinct_QMARK_.cljs$lang$arity$2 = distinct_QMARK___2;
distinct_QMARK_.cljs$lang$arity$variadic = distinct_QMARK___3.cljs$lang$arity$variadic;
return distinct_QMARK_;
})()
;
/**
* Comparator. Returns a negative number, zero, or a positive number
* when x is logically 'less than', 'equal to', or 'greater than'
* y. Uses IComparable if available and google.array.defaultCompare for objects
* of the same type and special-cases nil to be less than any other object.
*/
cljs.core.compare = (function compare(x,y){
if((x === y))
{return 0;
} else
{if((x == null))
{return -1;
} else
{if((y == null))
{return 1;
} else
{if((cljs.core.type.call(null,x) === cljs.core.type.call(null,y)))
{if((function (){var G__7192__7193 = x;
if(G__7192__7193)
{if(cljs.core.truth_((function (){var or__3824__auto____7194 = null;
if(cljs.core.truth_(or__3824__auto____7194))
{return or__3824__auto____7194;
} else
{return G__7192__7193.cljs$core$IComparable$;
}
})()))
{return true;
} else
{if((!G__7192__7193.cljs$lang$protocol_mask$partition$))
{return cljs.core.type_satisfies_.call(null,cljs.core.IComparable,G__7192__7193);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.IComparable,G__7192__7193);
}
})())
{return cljs.core._compare.call(null,x,y);
} else
{return goog.array.defaultCompare(x,y);
}
} else
{if("\uFDD0'else")
{throw (new Error("compare on non-nil objects of different types"));
} else
{return null;
}
}
}
}
}
});
/**
* Compare indexed collection.
*/
cljs.core.compare_indexed = (function() {
var compare_indexed = null;
var compare_indexed__2 = (function (xs,ys){
var xl__7199 = cljs.core.count.call(null,xs);
var yl__7200 = cljs.core.count.call(null,ys);
if((xl__7199 < yl__7200))
{return -1;
} else
{if((xl__7199 > yl__7200))
{return 1;
} else
{if("\uFDD0'else")
{return compare_indexed.call(null,xs,ys,xl__7199,0);
} else
{return null;
}
}
}
});
var compare_indexed__4 = (function (xs,ys,len,n){
while(true){
var d__7201 = cljs.core.compare.call(null,cljs.core.nth.call(null,xs,n),cljs.core.nth.call(null,ys,n));
if((function (){var and__3822__auto____7202 = (d__7201 === 0);
if(and__3822__auto____7202)
{return ((n + 1) < len);
} else
{return and__3822__auto____7202;
}
})())
{{
var G__7203 = xs;
var G__7204 = ys;
var G__7205 = len;
var G__7206 = (n + 1);
xs = G__7203;
ys = G__7204;
len = G__7205;
n = G__7206;
continue;
}
} else
{return d__7201;
}
break;
}
});
compare_indexed = function(xs,ys,len,n){
switch(arguments.length){
case 2:
return compare_indexed__2.call(this,xs,ys);
case 4:
return compare_indexed__4.call(this,xs,ys,len,n);
}
throw('Invalid arity: ' + arguments.length);
};
compare_indexed.cljs$lang$arity$2 = compare_indexed__2;
compare_indexed.cljs$lang$arity$4 = compare_indexed__4;
return compare_indexed;
})()
;
/**
* Given a fn that might be boolean valued or a comparator,
* return a fn that is a comparator.
*/
cljs.core.fn__GT_comparator = (function fn__GT_comparator(f){
if(cljs.core._EQ_.call(null,f,cljs.core.compare))
{return cljs.core.compare;
} else
{return (function (x,y){
var r__7208 = f.call(null,x,y);
if(cljs.core.number_QMARK_.call(null,r__7208))
{return r__7208;
} else
{if(cljs.core.truth_(r__7208))
{return -1;
} else
{if(cljs.core.truth_(f.call(null,y,x)))
{return 1;
} else
{return 0;
}
}
}
});
}
});
/**
* Returns a sorted sequence of the items in coll. Comp can be
* boolean-valued comparison funcion, or a -/0/+ valued comparator.
* Comp defaults to compare.
*/
cljs.core.sort = (function() {
var sort = null;
var sort__1 = (function (coll){
return sort.call(null,cljs.core.compare,coll);
});
var sort__2 = (function (comp,coll){
if(cljs.core.seq.call(null,coll))
{var a__7210 = cljs.core.to_array.call(null,coll);
goog.array.stableSort(a__7210,cljs.core.fn__GT_comparator.call(null,comp));
return cljs.core.seq.call(null,a__7210);
} else
{return cljs.core.List.EMPTY;
}
});
sort = function(comp,coll){
switch(arguments.length){
case 1:
return sort__1.call(this,comp);
case 2:
return sort__2.call(this,comp,coll);
}
throw('Invalid arity: ' + arguments.length);
};
sort.cljs$lang$arity$1 = sort__1;
sort.cljs$lang$arity$2 = sort__2;
return sort;
})()
;
/**
* Returns a sorted sequence of the items in coll, where the sort
* order is determined by comparing (keyfn item).  Comp can be
* boolean-valued comparison funcion, or a -/0/+ valued comparator.
* Comp defaults to compare.
*/
cljs.core.sort_by = (function() {
var sort_by = null;
var sort_by__2 = (function (keyfn,coll){
return sort_by.call(null,keyfn,cljs.core.compare,coll);
});
var sort_by__3 = (function (keyfn,comp,coll){
return cljs.core.sort.call(null,(function (x,y){
return cljs.core.fn__GT_comparator.call(null,comp).call(null,keyfn.call(null,x),keyfn.call(null,y));
}),coll);
});
sort_by = function(keyfn,comp,coll){
switch(arguments.length){
case 2:
return sort_by__2.call(this,keyfn,comp);
case 3:
return sort_by__3.call(this,keyfn,comp,coll);
}
throw('Invalid arity: ' + arguments.length);
};
sort_by.cljs$lang$arity$2 = sort_by__2;
sort_by.cljs$lang$arity$3 = sort_by__3;
return sort_by;
})()
;
cljs.core.seq_reduce = (function() {
var seq_reduce = null;
var seq_reduce__2 = (function (f,coll){
var temp__3971__auto____7216 = cljs.core.seq.call(null,coll);
if(temp__3971__auto____7216)
{var s__7217 = temp__3971__auto____7216;
return cljs.core.reduce.call(null,f,cljs.core.first.call(null,s__7217),cljs.core.next.call(null,s__7217));
} else
{return f.call(null);
}
});
var seq_reduce__3 = (function (f,val,coll){
var val__7218 = val;
var coll__7219 = cljs.core.seq.call(null,coll);
while(true){
if(coll__7219)
{var nval__7220 = f.call(null,val__7218,cljs.core.first.call(null,coll__7219));
if(cljs.core.reduced_QMARK_.call(null,nval__7220))
{return cljs.core.deref.call(null,nval__7220);
} else
{{
var G__7221 = nval__7220;
var G__7222 = cljs.core.next.call(null,coll__7219);
val__7218 = G__7221;
coll__7219 = G__7222;
continue;
}
}
} else
{return val__7218;
}
break;
}
});
seq_reduce = function(f,val,coll){
switch(arguments.length){
case 2:
return seq_reduce__2.call(this,f,val);
case 3:
return seq_reduce__3.call(this,f,val,coll);
}
throw('Invalid arity: ' + arguments.length);
};
seq_reduce.cljs$lang$arity$2 = seq_reduce__2;
seq_reduce.cljs$lang$arity$3 = seq_reduce__3;
return seq_reduce;
})()
;
/**
* Return a random permutation of coll
*/
cljs.core.shuffle = (function shuffle(coll){
var a__7224 = cljs.core.to_array.call(null,coll);
goog.array.shuffle(a__7224);
return cljs.core.vec.call(null,a__7224);
});
/**
* f should be a function of 2 arguments. If val is not supplied,
* returns the result of applying f to the first 2 items in coll, then
* applying f to that result and the 3rd item, etc. If coll contains no
* items, f must accept no arguments as well, and reduce returns the
* result of calling f with no arguments.  If coll has only 1 item, it
* is returned and f is not called.  If val is supplied, returns the
* result of applying f to val and the first item in coll, then
* applying f to that result and the 2nd item, etc. If coll contains no
* items, returns val and f is not called.
*/
cljs.core.reduce = (function() {
var reduce = null;
var reduce__2 = (function (f,coll){
if((function (){var G__7231__7232 = coll;
if(G__7231__7232)
{if((function (){var or__3824__auto____7233 = (G__7231__7232.cljs$lang$protocol_mask$partition0$ & 524288);
if(or__3824__auto____7233)
{return or__3824__auto____7233;
} else
{return G__7231__7232.cljs$core$IReduce$;
}
})())
{return true;
} else
{if((!G__7231__7232.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.IReduce,G__7231__7232);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.IReduce,G__7231__7232);
}
})())
{return cljs.core._reduce.call(null,coll,f);
} else
{return cljs.core.seq_reduce.call(null,f,coll);
}
});
var reduce__3 = (function (f,val,coll){
if((function (){var G__7234__7235 = coll;
if(G__7234__7235)
{if((function (){var or__3824__auto____7236 = (G__7234__7235.cljs$lang$protocol_mask$partition0$ & 524288);
if(or__3824__auto____7236)
{return or__3824__auto____7236;
} else
{return G__7234__7235.cljs$core$IReduce$;
}
})())
{return true;
} else
{if((!G__7234__7235.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.IReduce,G__7234__7235);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.IReduce,G__7234__7235);
}
})())
{return cljs.core._reduce.call(null,coll,f,val);
} else
{return cljs.core.seq_reduce.call(null,f,val,coll);
}
});
reduce = function(f,val,coll){
switch(arguments.length){
case 2:
return reduce__2.call(this,f,val);
case 3:
return reduce__3.call(this,f,val,coll);
}
throw('Invalid arity: ' + arguments.length);
};
reduce.cljs$lang$arity$2 = reduce__2;
reduce.cljs$lang$arity$3 = reduce__3;
return reduce;
})()
;
/**
* Reduces an associative collection. f should be a function of 3
* arguments. Returns the result of applying f to init, the first key
* and the first value in coll, then applying f to that result and the
* 2nd key and value, etc. If coll contains no entries, returns init
* and f is not called. Note that reduce-kv is supported on vectors,
* where the keys will be the ordinals.
*/
cljs.core.reduce_kv = (function reduce_kv(f,init,coll){
return cljs.core._kv_reduce.call(null,coll,f,init);
});

/**
* @constructor
*/
cljs.core.Reduced = (function (val){
this.val = val;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 32768;
})
cljs.core.Reduced.cljs$lang$type = true;
cljs.core.Reduced.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/Reduced");
});
cljs.core.Reduced.prototype.cljs$core$IDeref$_deref$arity$1 = (function (o){
var this__7237 = this;
return this__7237.val;
});
cljs.core.Reduced;
/**
* Returns true if x is the result of a call to reduced
*/
cljs.core.reduced_QMARK_ = (function reduced_QMARK_(r){
return cljs.core.instance_QMARK_.call(null,cljs.core.Reduced,r);
});
/**
* Wraps x in a way such that a reduce will terminate with the value x
*/
cljs.core.reduced = (function reduced(x){
return (new cljs.core.Reduced(x));
});
/**
* Returns the sum of nums. (+) returns 0.
* @param {...*} var_args
*/
cljs.core._PLUS_ = (function() {
var _PLUS_ = null;
var _PLUS___0 = (function (){
return 0;
});
var _PLUS___1 = (function (x){
return x;
});
var _PLUS___2 = (function (x,y){
return (x + y);
});
var _PLUS___3 = (function() { 
var G__7238__delegate = function (x,y,more){
return cljs.core.reduce.call(null,_PLUS_,(x + y),more);
};
var G__7238 = function (x,y,var_args){
var more = null;
if (goog.isDef(var_args)) {
  more = cljs.core.array_seq(Array.prototype.slice.call(arguments, 2),0);
} 
return G__7238__delegate.call(this, x, y, more);
};
G__7238.cljs$lang$maxFixedArity = 2;
G__7238.cljs$lang$applyTo = (function (arglist__7239){
var x = cljs.core.first(arglist__7239);
var y = cljs.core.first(cljs.core.next(arglist__7239));
var more = cljs.core.rest(cljs.core.next(arglist__7239));
return G__7238__delegate(x, y, more);
});
G__7238.cljs$lang$arity$variadic = G__7238__delegate;
return G__7238;
})()
;
_PLUS_ = function(x,y,var_args){
var more = var_args;
switch(arguments.length){
case 0:
return _PLUS___0.call(this);
case 1:
return _PLUS___1.call(this,x);
case 2:
return _PLUS___2.call(this,x,y);
default:
return _PLUS___3.cljs$lang$arity$variadic(x,y, cljs.core.array_seq(arguments, 2));
}
throw('Invalid arity: ' + arguments.length);
};
_PLUS_.cljs$lang$maxFixedArity = 2;
_PLUS_.cljs$lang$applyTo = _PLUS___3.cljs$lang$applyTo;
_PLUS_.cljs$lang$arity$0 = _PLUS___0;
_PLUS_.cljs$lang$arity$1 = _PLUS___1;
_PLUS_.cljs$lang$arity$2 = _PLUS___2;
_PLUS_.cljs$lang$arity$variadic = _PLUS___3.cljs$lang$arity$variadic;
return _PLUS_;
})()
;
/**
* If no ys are supplied, returns the negation of x, else subtracts
* the ys from x and returns the result.
* @param {...*} var_args
*/
cljs.core._ = (function() {
var _ = null;
var ___1 = (function (x){
return (- x);
});
var ___2 = (function (x,y){
return (x - y);
});
var ___3 = (function() { 
var G__7240__delegate = function (x,y,more){
return cljs.core.reduce.call(null,_,(x - y),more);
};
var G__7240 = function (x,y,var_args){
var more = null;
if (goog.isDef(var_args)) {
  more = cljs.core.array_seq(Array.prototype.slice.call(arguments, 2),0);
} 
return G__7240__delegate.call(this, x, y, more);
};
G__7240.cljs$lang$maxFixedArity = 2;
G__7240.cljs$lang$applyTo = (function (arglist__7241){
var x = cljs.core.first(arglist__7241);
var y = cljs.core.first(cljs.core.next(arglist__7241));
var more = cljs.core.rest(cljs.core.next(arglist__7241));
return G__7240__delegate(x, y, more);
});
G__7240.cljs$lang$arity$variadic = G__7240__delegate;
return G__7240;
})()
;
_ = function(x,y,var_args){
var more = var_args;
switch(arguments.length){
case 1:
return ___1.call(this,x);
case 2:
return ___2.call(this,x,y);
default:
return ___3.cljs$lang$arity$variadic(x,y, cljs.core.array_seq(arguments, 2));
}
throw('Invalid arity: ' + arguments.length);
};
_.cljs$lang$maxFixedArity = 2;
_.cljs$lang$applyTo = ___3.cljs$lang$applyTo;
_.cljs$lang$arity$1 = ___1;
_.cljs$lang$arity$2 = ___2;
_.cljs$lang$arity$variadic = ___3.cljs$lang$arity$variadic;
return _;
})()
;
/**
* Returns the product of nums. (*) returns 1.
* @param {...*} var_args
*/
cljs.core._STAR_ = (function() {
var _STAR_ = null;
var _STAR___0 = (function (){
return 1;
});
var _STAR___1 = (function (x){
return x;
});
var _STAR___2 = (function (x,y){
return (x * y);
});
var _STAR___3 = (function() { 
var G__7242__delegate = function (x,y,more){
return cljs.core.reduce.call(null,_STAR_,(x * y),more);
};
var G__7242 = function (x,y,var_args){
var more = null;
if (goog.isDef(var_args)) {
  more = cljs.core.array_seq(Array.prototype.slice.call(arguments, 2),0);
} 
return G__7242__delegate.call(this, x, y, more);
};
G__7242.cljs$lang$maxFixedArity = 2;
G__7242.cljs$lang$applyTo = (function (arglist__7243){
var x = cljs.core.first(arglist__7243);
var y = cljs.core.first(cljs.core.next(arglist__7243));
var more = cljs.core.rest(cljs.core.next(arglist__7243));
return G__7242__delegate(x, y, more);
});
G__7242.cljs$lang$arity$variadic = G__7242__delegate;
return G__7242;
})()
;
_STAR_ = function(x,y,var_args){
var more = var_args;
switch(arguments.length){
case 0:
return _STAR___0.call(this);
case 1:
return _STAR___1.call(this,x);
case 2:
return _STAR___2.call(this,x,y);
default:
return _STAR___3.cljs$lang$arity$variadic(x,y, cljs.core.array_seq(arguments, 2));
}
throw('Invalid arity: ' + arguments.length);
};
_STAR_.cljs$lang$maxFixedArity = 2;
_STAR_.cljs$lang$applyTo = _STAR___3.cljs$lang$applyTo;
_STAR_.cljs$lang$arity$0 = _STAR___0;
_STAR_.cljs$lang$arity$1 = _STAR___1;
_STAR_.cljs$lang$arity$2 = _STAR___2;
_STAR_.cljs$lang$arity$variadic = _STAR___3.cljs$lang$arity$variadic;
return _STAR_;
})()
;
/**
* If no denominators are supplied, returns 1/numerator,
* else returns numerator divided by all of the denominators.
* @param {...*} var_args
*/
cljs.core._SLASH_ = (function() {
var _SLASH_ = null;
var _SLASH___1 = (function (x){
return _SLASH_.call(null,1,x);
});
var _SLASH___2 = (function (x,y){
return (x / y);
});
var _SLASH___3 = (function() { 
var G__7244__delegate = function (x,y,more){
return cljs.core.reduce.call(null,_SLASH_,_SLASH_.call(null,x,y),more);
};
var G__7244 = function (x,y,var_args){
var more = null;
if (goog.isDef(var_args)) {
  more = cljs.core.array_seq(Array.prototype.slice.call(arguments, 2),0);
} 
return G__7244__delegate.call(this, x, y, more);
};
G__7244.cljs$lang$maxFixedArity = 2;
G__7244.cljs$lang$applyTo = (function (arglist__7245){
var x = cljs.core.first(arglist__7245);
var y = cljs.core.first(cljs.core.next(arglist__7245));
var more = cljs.core.rest(cljs.core.next(arglist__7245));
return G__7244__delegate(x, y, more);
});
G__7244.cljs$lang$arity$variadic = G__7244__delegate;
return G__7244;
})()
;
_SLASH_ = function(x,y,var_args){
var more = var_args;
switch(arguments.length){
case 1:
return _SLASH___1.call(this,x);
case 2:
return _SLASH___2.call(this,x,y);
default:
return _SLASH___3.cljs$lang$arity$variadic(x,y, cljs.core.array_seq(arguments, 2));
}
throw('Invalid arity: ' + arguments.length);
};
_SLASH_.cljs$lang$maxFixedArity = 2;
_SLASH_.cljs$lang$applyTo = _SLASH___3.cljs$lang$applyTo;
_SLASH_.cljs$lang$arity$1 = _SLASH___1;
_SLASH_.cljs$lang$arity$2 = _SLASH___2;
_SLASH_.cljs$lang$arity$variadic = _SLASH___3.cljs$lang$arity$variadic;
return _SLASH_;
})()
;
/**
* Returns non-nil if nums are in monotonically increasing order,
* otherwise false.
* @param {...*} var_args
*/
cljs.core._LT_ = (function() {
var _LT_ = null;
var _LT___1 = (function (x){
return true;
});
var _LT___2 = (function (x,y){
return (x < y);
});
var _LT___3 = (function() { 
var G__7246__delegate = function (x,y,more){
while(true){
if((x < y))
{if(cljs.core.next.call(null,more))
{{
var G__7247 = y;
var G__7248 = cljs.core.first.call(null,more);
var G__7249 = cljs.core.next.call(null,more);
x = G__7247;
y = G__7248;
more = G__7249;
continue;
}
} else
{return (y < cljs.core.first.call(null,more));
}
} else
{return false;
}
break;
}
};
var G__7246 = function (x,y,var_args){
var more = null;
if (goog.isDef(var_args)) {
  more = cljs.core.array_seq(Array.prototype.slice.call(arguments, 2),0);
} 
return G__7246__delegate.call(this, x, y, more);
};
G__7246.cljs$lang$maxFixedArity = 2;
G__7246.cljs$lang$applyTo = (function (arglist__7250){
var x = cljs.core.first(arglist__7250);
var y = cljs.core.first(cljs.core.next(arglist__7250));
var more = cljs.core.rest(cljs.core.next(arglist__7250));
return G__7246__delegate(x, y, more);
});
G__7246.cljs$lang$arity$variadic = G__7246__delegate;
return G__7246;
})()
;
_LT_ = function(x,y,var_args){
var more = var_args;
switch(arguments.length){
case 1:
return _LT___1.call(this,x);
case 2:
return _LT___2.call(this,x,y);
default:
return _LT___3.cljs$lang$arity$variadic(x,y, cljs.core.array_seq(arguments, 2));
}
throw('Invalid arity: ' + arguments.length);
};
_LT_.cljs$lang$maxFixedArity = 2;
_LT_.cljs$lang$applyTo = _LT___3.cljs$lang$applyTo;
_LT_.cljs$lang$arity$1 = _LT___1;
_LT_.cljs$lang$arity$2 = _LT___2;
_LT_.cljs$lang$arity$variadic = _LT___3.cljs$lang$arity$variadic;
return _LT_;
})()
;
/**
* Returns non-nil if nums are in monotonically non-decreasing order,
* otherwise false.
* @param {...*} var_args
*/
cljs.core._LT__EQ_ = (function() {
var _LT__EQ_ = null;
var _LT__EQ___1 = (function (x){
return true;
});
var _LT__EQ___2 = (function (x,y){
return (x <= y);
});
var _LT__EQ___3 = (function() { 
var G__7251__delegate = function (x,y,more){
while(true){
if((x <= y))
{if(cljs.core.next.call(null,more))
{{
var G__7252 = y;
var G__7253 = cljs.core.first.call(null,more);
var G__7254 = cljs.core.next.call(null,more);
x = G__7252;
y = G__7253;
more = G__7254;
continue;
}
} else
{return (y <= cljs.core.first.call(null,more));
}
} else
{return false;
}
break;
}
};
var G__7251 = function (x,y,var_args){
var more = null;
if (goog.isDef(var_args)) {
  more = cljs.core.array_seq(Array.prototype.slice.call(arguments, 2),0);
} 
return G__7251__delegate.call(this, x, y, more);
};
G__7251.cljs$lang$maxFixedArity = 2;
G__7251.cljs$lang$applyTo = (function (arglist__7255){
var x = cljs.core.first(arglist__7255);
var y = cljs.core.first(cljs.core.next(arglist__7255));
var more = cljs.core.rest(cljs.core.next(arglist__7255));
return G__7251__delegate(x, y, more);
});
G__7251.cljs$lang$arity$variadic = G__7251__delegate;
return G__7251;
})()
;
_LT__EQ_ = function(x,y,var_args){
var more = var_args;
switch(arguments.length){
case 1:
return _LT__EQ___1.call(this,x);
case 2:
return _LT__EQ___2.call(this,x,y);
default:
return _LT__EQ___3.cljs$lang$arity$variadic(x,y, cljs.core.array_seq(arguments, 2));
}
throw('Invalid arity: ' + arguments.length);
};
_LT__EQ_.cljs$lang$maxFixedArity = 2;
_LT__EQ_.cljs$lang$applyTo = _LT__EQ___3.cljs$lang$applyTo;
_LT__EQ_.cljs$lang$arity$1 = _LT__EQ___1;
_LT__EQ_.cljs$lang$arity$2 = _LT__EQ___2;
_LT__EQ_.cljs$lang$arity$variadic = _LT__EQ___3.cljs$lang$arity$variadic;
return _LT__EQ_;
})()
;
/**
* Returns non-nil if nums are in monotonically decreasing order,
* otherwise false.
* @param {...*} var_args
*/
cljs.core._GT_ = (function() {
var _GT_ = null;
var _GT___1 = (function (x){
return true;
});
var _GT___2 = (function (x,y){
return (x > y);
});
var _GT___3 = (function() { 
var G__7256__delegate = function (x,y,more){
while(true){
if((x > y))
{if(cljs.core.next.call(null,more))
{{
var G__7257 = y;
var G__7258 = cljs.core.first.call(null,more);
var G__7259 = cljs.core.next.call(null,more);
x = G__7257;
y = G__7258;
more = G__7259;
continue;
}
} else
{return (y > cljs.core.first.call(null,more));
}
} else
{return false;
}
break;
}
};
var G__7256 = function (x,y,var_args){
var more = null;
if (goog.isDef(var_args)) {
  more = cljs.core.array_seq(Array.prototype.slice.call(arguments, 2),0);
} 
return G__7256__delegate.call(this, x, y, more);
};
G__7256.cljs$lang$maxFixedArity = 2;
G__7256.cljs$lang$applyTo = (function (arglist__7260){
var x = cljs.core.first(arglist__7260);
var y = cljs.core.first(cljs.core.next(arglist__7260));
var more = cljs.core.rest(cljs.core.next(arglist__7260));
return G__7256__delegate(x, y, more);
});
G__7256.cljs$lang$arity$variadic = G__7256__delegate;
return G__7256;
})()
;
_GT_ = function(x,y,var_args){
var more = var_args;
switch(arguments.length){
case 1:
return _GT___1.call(this,x);
case 2:
return _GT___2.call(this,x,y);
default:
return _GT___3.cljs$lang$arity$variadic(x,y, cljs.core.array_seq(arguments, 2));
}
throw('Invalid arity: ' + arguments.length);
};
_GT_.cljs$lang$maxFixedArity = 2;
_GT_.cljs$lang$applyTo = _GT___3.cljs$lang$applyTo;
_GT_.cljs$lang$arity$1 = _GT___1;
_GT_.cljs$lang$arity$2 = _GT___2;
_GT_.cljs$lang$arity$variadic = _GT___3.cljs$lang$arity$variadic;
return _GT_;
})()
;
/**
* Returns non-nil if nums are in monotonically non-increasing order,
* otherwise false.
* @param {...*} var_args
*/
cljs.core._GT__EQ_ = (function() {
var _GT__EQ_ = null;
var _GT__EQ___1 = (function (x){
return true;
});
var _GT__EQ___2 = (function (x,y){
return (x >= y);
});
var _GT__EQ___3 = (function() { 
var G__7261__delegate = function (x,y,more){
while(true){
if((x >= y))
{if(cljs.core.next.call(null,more))
{{
var G__7262 = y;
var G__7263 = cljs.core.first.call(null,more);
var G__7264 = cljs.core.next.call(null,more);
x = G__7262;
y = G__7263;
more = G__7264;
continue;
}
} else
{return (y >= cljs.core.first.call(null,more));
}
} else
{return false;
}
break;
}
};
var G__7261 = function (x,y,var_args){
var more = null;
if (goog.isDef(var_args)) {
  more = cljs.core.array_seq(Array.prototype.slice.call(arguments, 2),0);
} 
return G__7261__delegate.call(this, x, y, more);
};
G__7261.cljs$lang$maxFixedArity = 2;
G__7261.cljs$lang$applyTo = (function (arglist__7265){
var x = cljs.core.first(arglist__7265);
var y = cljs.core.first(cljs.core.next(arglist__7265));
var more = cljs.core.rest(cljs.core.next(arglist__7265));
return G__7261__delegate(x, y, more);
});
G__7261.cljs$lang$arity$variadic = G__7261__delegate;
return G__7261;
})()
;
_GT__EQ_ = function(x,y,var_args){
var more = var_args;
switch(arguments.length){
case 1:
return _GT__EQ___1.call(this,x);
case 2:
return _GT__EQ___2.call(this,x,y);
default:
return _GT__EQ___3.cljs$lang$arity$variadic(x,y, cljs.core.array_seq(arguments, 2));
}
throw('Invalid arity: ' + arguments.length);
};
_GT__EQ_.cljs$lang$maxFixedArity = 2;
_GT__EQ_.cljs$lang$applyTo = _GT__EQ___3.cljs$lang$applyTo;
_GT__EQ_.cljs$lang$arity$1 = _GT__EQ___1;
_GT__EQ_.cljs$lang$arity$2 = _GT__EQ___2;
_GT__EQ_.cljs$lang$arity$variadic = _GT__EQ___3.cljs$lang$arity$variadic;
return _GT__EQ_;
})()
;
/**
* Returns a number one less than num.
*/
cljs.core.dec = (function dec(x){
return (x - 1);
});
/**
* Returns the greatest of the nums.
* @param {...*} var_args
*/
cljs.core.max = (function() {
var max = null;
var max__1 = (function (x){
return x;
});
var max__2 = (function (x,y){
return ((x > y) ? x : y);
});
var max__3 = (function() { 
var G__7266__delegate = function (x,y,more){
return cljs.core.reduce.call(null,max,((x > y) ? x : y),more);
};
var G__7266 = function (x,y,var_args){
var more = null;
if (goog.isDef(var_args)) {
  more = cljs.core.array_seq(Array.prototype.slice.call(arguments, 2),0);
} 
return G__7266__delegate.call(this, x, y, more);
};
G__7266.cljs$lang$maxFixedArity = 2;
G__7266.cljs$lang$applyTo = (function (arglist__7267){
var x = cljs.core.first(arglist__7267);
var y = cljs.core.first(cljs.core.next(arglist__7267));
var more = cljs.core.rest(cljs.core.next(arglist__7267));
return G__7266__delegate(x, y, more);
});
G__7266.cljs$lang$arity$variadic = G__7266__delegate;
return G__7266;
})()
;
max = function(x,y,var_args){
var more = var_args;
switch(arguments.length){
case 1:
return max__1.call(this,x);
case 2:
return max__2.call(this,x,y);
default:
return max__3.cljs$lang$arity$variadic(x,y, cljs.core.array_seq(arguments, 2));
}
throw('Invalid arity: ' + arguments.length);
};
max.cljs$lang$maxFixedArity = 2;
max.cljs$lang$applyTo = max__3.cljs$lang$applyTo;
max.cljs$lang$arity$1 = max__1;
max.cljs$lang$arity$2 = max__2;
max.cljs$lang$arity$variadic = max__3.cljs$lang$arity$variadic;
return max;
})()
;
/**
* Returns the least of the nums.
* @param {...*} var_args
*/
cljs.core.min = (function() {
var min = null;
var min__1 = (function (x){
return x;
});
var min__2 = (function (x,y){
return ((x < y) ? x : y);
});
var min__3 = (function() { 
var G__7268__delegate = function (x,y,more){
return cljs.core.reduce.call(null,min,((x < y) ? x : y),more);
};
var G__7268 = function (x,y,var_args){
var more = null;
if (goog.isDef(var_args)) {
  more = cljs.core.array_seq(Array.prototype.slice.call(arguments, 2),0);
} 
return G__7268__delegate.call(this, x, y, more);
};
G__7268.cljs$lang$maxFixedArity = 2;
G__7268.cljs$lang$applyTo = (function (arglist__7269){
var x = cljs.core.first(arglist__7269);
var y = cljs.core.first(cljs.core.next(arglist__7269));
var more = cljs.core.rest(cljs.core.next(arglist__7269));
return G__7268__delegate(x, y, more);
});
G__7268.cljs$lang$arity$variadic = G__7268__delegate;
return G__7268;
})()
;
min = function(x,y,var_args){
var more = var_args;
switch(arguments.length){
case 1:
return min__1.call(this,x);
case 2:
return min__2.call(this,x,y);
default:
return min__3.cljs$lang$arity$variadic(x,y, cljs.core.array_seq(arguments, 2));
}
throw('Invalid arity: ' + arguments.length);
};
min.cljs$lang$maxFixedArity = 2;
min.cljs$lang$applyTo = min__3.cljs$lang$applyTo;
min.cljs$lang$arity$1 = min__1;
min.cljs$lang$arity$2 = min__2;
min.cljs$lang$arity$variadic = min__3.cljs$lang$arity$variadic;
return min;
})()
;
cljs.core.fix = (function fix(q){
if((q >= 0))
{return Math.floor.call(null,q);
} else
{return Math.ceil.call(null,q);
}
});
/**
* Coerce to int by stripping decimal places.
*/
cljs.core.int$ = (function int$(x){
return cljs.core.fix.call(null,x);
});
/**
* Coerce to long by stripping decimal places. Identical to `int'.
*/
cljs.core.long$ = (function long$(x){
return cljs.core.fix.call(null,x);
});
/**
* Modulus of num and div. Truncates toward negative infinity.
*/
cljs.core.mod = (function mod(n,d){
return (n % d);
});
/**
* quot[ient] of dividing numerator by denominator.
*/
cljs.core.quot = (function quot(n,d){
var rem__7271 = (n % d);
return cljs.core.fix.call(null,((n - rem__7271) / d));
});
/**
* remainder of dividing numerator by denominator.
*/
cljs.core.rem = (function rem(n,d){
var q__7273 = cljs.core.quot.call(null,n,d);
return (n - (d * q__7273));
});
/**
* Returns a random floating point number between 0 (inclusive) and n (default 1) (exclusive).
*/
cljs.core.rand = (function() {
var rand = null;
var rand__0 = (function (){
return Math.random.call(null);
});
var rand__1 = (function (n){
return (n * rand.call(null));
});
rand = function(n){
switch(arguments.length){
case 0:
return rand__0.call(this);
case 1:
return rand__1.call(this,n);
}
throw('Invalid arity: ' + arguments.length);
};
rand.cljs$lang$arity$0 = rand__0;
rand.cljs$lang$arity$1 = rand__1;
return rand;
})()
;
/**
* Returns a random integer between 0 (inclusive) and n (exclusive).
*/
cljs.core.rand_int = (function rand_int(n){
return cljs.core.fix.call(null,cljs.core.rand.call(null,n));
});
/**
* Bitwise exclusive or
*/
cljs.core.bit_xor = (function bit_xor(x,y){
return (x ^ y);
});
/**
* Bitwise and
*/
cljs.core.bit_and = (function bit_and(x,y){
return (x & y);
});
/**
* Bitwise or
*/
cljs.core.bit_or = (function bit_or(x,y){
return (x | y);
});
/**
* Bitwise and
*/
cljs.core.bit_and_not = (function bit_and_not(x,y){
return (x & ~y);
});
/**
* Clear bit at index n
*/
cljs.core.bit_clear = (function bit_clear(x,n){
return (x & ~(1 << n));
});
/**
* Flip bit at index n
*/
cljs.core.bit_flip = (function bit_flip(x,n){
return (x ^ (1 << n));
});
/**
* Bitwise complement
*/
cljs.core.bit_not = (function bit_not(x){
return (~ x);
});
/**
* Set bit at index n
*/
cljs.core.bit_set = (function bit_set(x,n){
return (x | (1 << n));
});
/**
* Test bit at index n
*/
cljs.core.bit_test = (function bit_test(x,n){
return ((x & (1 << n)) != 0);
});
/**
* Bitwise shift left
*/
cljs.core.bit_shift_left = (function bit_shift_left(x,n){
return (x << n);
});
/**
* Bitwise shift right
*/
cljs.core.bit_shift_right = (function bit_shift_right(x,n){
return (x >> n);
});
/**
* Bitwise shift right with zero fill
*/
cljs.core.bit_shift_right_zero_fill = (function bit_shift_right_zero_fill(x,n){
return (x >>> n);
});
/**
* Counts the number of bits set in n
*/
cljs.core.bit_count = (function bit_count(v){
var v__7276 = (v - ((v >> 1) & 1431655765));
var v__7277 = ((v__7276 & 858993459) + ((v__7276 >> 2) & 858993459));
return ((((v__7277 + (v__7277 >> 4)) & 252645135) * 16843009) >> 24);
});
/**
* Returns non-nil if nums all have the equivalent
* value, otherwise false. Behavior on non nums is
* undefined.
* @param {...*} var_args
*/
cljs.core._EQ__EQ_ = (function() {
var _EQ__EQ_ = null;
var _EQ__EQ___1 = (function (x){
return true;
});
var _EQ__EQ___2 = (function (x,y){
return cljs.core._equiv.call(null,x,y);
});
var _EQ__EQ___3 = (function() { 
var G__7278__delegate = function (x,y,more){
while(true){
if(cljs.core.truth_(_EQ__EQ_.call(null,x,y)))
{if(cljs.core.next.call(null,more))
{{
var G__7279 = y;
var G__7280 = cljs.core.first.call(null,more);
var G__7281 = cljs.core.next.call(null,more);
x = G__7279;
y = G__7280;
more = G__7281;
continue;
}
} else
{return _EQ__EQ_.call(null,y,cljs.core.first.call(null,more));
}
} else
{return false;
}
break;
}
};
var G__7278 = function (x,y,var_args){
var more = null;
if (goog.isDef(var_args)) {
  more = cljs.core.array_seq(Array.prototype.slice.call(arguments, 2),0);
} 
return G__7278__delegate.call(this, x, y, more);
};
G__7278.cljs$lang$maxFixedArity = 2;
G__7278.cljs$lang$applyTo = (function (arglist__7282){
var x = cljs.core.first(arglist__7282);
var y = cljs.core.first(cljs.core.next(arglist__7282));
var more = cljs.core.rest(cljs.core.next(arglist__7282));
return G__7278__delegate(x, y, more);
});
G__7278.cljs$lang$arity$variadic = G__7278__delegate;
return G__7278;
})()
;
_EQ__EQ_ = function(x,y,var_args){
var more = var_args;
switch(arguments.length){
case 1:
return _EQ__EQ___1.call(this,x);
case 2:
return _EQ__EQ___2.call(this,x,y);
default:
return _EQ__EQ___3.cljs$lang$arity$variadic(x,y, cljs.core.array_seq(arguments, 2));
}
throw('Invalid arity: ' + arguments.length);
};
_EQ__EQ_.cljs$lang$maxFixedArity = 2;
_EQ__EQ_.cljs$lang$applyTo = _EQ__EQ___3.cljs$lang$applyTo;
_EQ__EQ_.cljs$lang$arity$1 = _EQ__EQ___1;
_EQ__EQ_.cljs$lang$arity$2 = _EQ__EQ___2;
_EQ__EQ_.cljs$lang$arity$variadic = _EQ__EQ___3.cljs$lang$arity$variadic;
return _EQ__EQ_;
})()
;
/**
* Returns true if num is greater than zero, else false
*/
cljs.core.pos_QMARK_ = (function pos_QMARK_(n){
return (n > 0);
});
cljs.core.zero_QMARK_ = (function zero_QMARK_(n){
return (n === 0);
});
/**
* Returns true if num is less than zero, else false
*/
cljs.core.neg_QMARK_ = (function neg_QMARK_(x){
return (x < 0);
});
/**
* Returns the nth next of coll, (seq coll) when n is 0.
*/
cljs.core.nthnext = (function nthnext(coll,n){
var n__7286 = n;
var xs__7287 = cljs.core.seq.call(null,coll);
while(true){
if(cljs.core.truth_((function (){var and__3822__auto____7288 = xs__7287;
if(and__3822__auto____7288)
{return (n__7286 > 0);
} else
{return and__3822__auto____7288;
}
})()))
{{
var G__7289 = (n__7286 - 1);
var G__7290 = cljs.core.next.call(null,xs__7287);
n__7286 = G__7289;
xs__7287 = G__7290;
continue;
}
} else
{return xs__7287;
}
break;
}
});
/**
* Internal - do not use!
* @param {...*} var_args
*/
cljs.core.str_STAR_ = (function() {
var str_STAR_ = null;
var str_STAR___0 = (function (){
return "";
});
var str_STAR___1 = (function (x){
if((x == null))
{return "";
} else
{if("\uFDD0'else")
{return x.toString();
} else
{return null;
}
}
});
var str_STAR___2 = (function() { 
var G__7291__delegate = function (x,ys){
return (function (sb,more){
while(true){
if(cljs.core.truth_(more))
{{
var G__7292 = sb.append(str_STAR_.call(null,cljs.core.first.call(null,more)));
var G__7293 = cljs.core.next.call(null,more);
sb = G__7292;
more = G__7293;
continue;
}
} else
{return str_STAR_.call(null,sb);
}
break;
}
}).call(null,(new goog.string.StringBuffer(str_STAR_.call(null,x))),ys);
};
var G__7291 = function (x,var_args){
var ys = null;
if (goog.isDef(var_args)) {
  ys = cljs.core.array_seq(Array.prototype.slice.call(arguments, 1),0);
} 
return G__7291__delegate.call(this, x, ys);
};
G__7291.cljs$lang$maxFixedArity = 1;
G__7291.cljs$lang$applyTo = (function (arglist__7294){
var x = cljs.core.first(arglist__7294);
var ys = cljs.core.rest(arglist__7294);
return G__7291__delegate(x, ys);
});
G__7291.cljs$lang$arity$variadic = G__7291__delegate;
return G__7291;
})()
;
str_STAR_ = function(x,var_args){
var ys = var_args;
switch(arguments.length){
case 0:
return str_STAR___0.call(this);
case 1:
return str_STAR___1.call(this,x);
default:
return str_STAR___2.cljs$lang$arity$variadic(x, cljs.core.array_seq(arguments, 1));
}
throw('Invalid arity: ' + arguments.length);
};
str_STAR_.cljs$lang$maxFixedArity = 1;
str_STAR_.cljs$lang$applyTo = str_STAR___2.cljs$lang$applyTo;
str_STAR_.cljs$lang$arity$0 = str_STAR___0;
str_STAR_.cljs$lang$arity$1 = str_STAR___1;
str_STAR_.cljs$lang$arity$variadic = str_STAR___2.cljs$lang$arity$variadic;
return str_STAR_;
})()
;
/**
* With no args, returns the empty string. With one arg x, returns
* x.toString().  (str nil) returns the empty string. With more than
* one arg, returns the concatenation of the str values of the args.
* @param {...*} var_args
*/
cljs.core.str = (function() {
var str = null;
var str__0 = (function (){
return "";
});
var str__1 = (function (x){
if(cljs.core.symbol_QMARK_.call(null,x))
{return x.substring(2,x.length);
} else
{if(cljs.core.keyword_QMARK_.call(null,x))
{return cljs.core.str_STAR_.call(null,":",x.substring(2,x.length));
} else
{if((x == null))
{return "";
} else
{if("\uFDD0'else")
{return x.toString();
} else
{return null;
}
}
}
}
});
var str__2 = (function() { 
var G__7295__delegate = function (x,ys){
return (function (sb,more){
while(true){
if(cljs.core.truth_(more))
{{
var G__7296 = sb.append(str.call(null,cljs.core.first.call(null,more)));
var G__7297 = cljs.core.next.call(null,more);
sb = G__7296;
more = G__7297;
continue;
}
} else
{return cljs.core.str_STAR_.call(null,sb);
}
break;
}
}).call(null,(new goog.string.StringBuffer(str.call(null,x))),ys);
};
var G__7295 = function (x,var_args){
var ys = null;
if (goog.isDef(var_args)) {
  ys = cljs.core.array_seq(Array.prototype.slice.call(arguments, 1),0);
} 
return G__7295__delegate.call(this, x, ys);
};
G__7295.cljs$lang$maxFixedArity = 1;
G__7295.cljs$lang$applyTo = (function (arglist__7298){
var x = cljs.core.first(arglist__7298);
var ys = cljs.core.rest(arglist__7298);
return G__7295__delegate(x, ys);
});
G__7295.cljs$lang$arity$variadic = G__7295__delegate;
return G__7295;
})()
;
str = function(x,var_args){
var ys = var_args;
switch(arguments.length){
case 0:
return str__0.call(this);
case 1:
return str__1.call(this,x);
default:
return str__2.cljs$lang$arity$variadic(x, cljs.core.array_seq(arguments, 1));
}
throw('Invalid arity: ' + arguments.length);
};
str.cljs$lang$maxFixedArity = 1;
str.cljs$lang$applyTo = str__2.cljs$lang$applyTo;
str.cljs$lang$arity$0 = str__0;
str.cljs$lang$arity$1 = str__1;
str.cljs$lang$arity$variadic = str__2.cljs$lang$arity$variadic;
return str;
})()
;
/**
* Returns the substring of s beginning at start inclusive, and ending
* at end (defaults to length of string), exclusive.
*/
cljs.core.subs = (function() {
var subs = null;
var subs__2 = (function (s,start){
return s.substring(start);
});
var subs__3 = (function (s,start,end){
return s.substring(start,end);
});
subs = function(s,start,end){
switch(arguments.length){
case 2:
return subs__2.call(this,s,start);
case 3:
return subs__3.call(this,s,start,end);
}
throw('Invalid arity: ' + arguments.length);
};
subs.cljs$lang$arity$2 = subs__2;
subs.cljs$lang$arity$3 = subs__3;
return subs;
})()
;
/**
* Formats a string using goog.string.format.
* @param {...*} var_args
*/
cljs.core.format = (function() { 
var format__delegate = function (fmt,args){
return cljs.core.apply.call(null,goog.string.format,fmt,args);
};
var format = function (fmt,var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 1),0);
} 
return format__delegate.call(this, fmt, args);
};
format.cljs$lang$maxFixedArity = 1;
format.cljs$lang$applyTo = (function (arglist__7299){
var fmt = cljs.core.first(arglist__7299);
var args = cljs.core.rest(arglist__7299);
return format__delegate(fmt, args);
});
format.cljs$lang$arity$variadic = format__delegate;
return format;
})()
;
/**
* Returns a Symbol with the given namespace and name.
*/
cljs.core.symbol = (function() {
var symbol = null;
var symbol__1 = (function (name){
if(cljs.core.symbol_QMARK_.call(null,name))
{name;
} else
{if(cljs.core.keyword_QMARK_.call(null,name))
{cljs.core.str_STAR_.call(null,"\uFDD1","'",cljs.core.subs.call(null,name,2));
} else
{}
}
return cljs.core.str_STAR_.call(null,"\uFDD1","'",name);
});
var symbol__2 = (function (ns,name){
return symbol.call(null,cljs.core.str_STAR_.call(null,ns,"/",name));
});
symbol = function(ns,name){
switch(arguments.length){
case 1:
return symbol__1.call(this,ns);
case 2:
return symbol__2.call(this,ns,name);
}
throw('Invalid arity: ' + arguments.length);
};
symbol.cljs$lang$arity$1 = symbol__1;
symbol.cljs$lang$arity$2 = symbol__2;
return symbol;
})()
;
/**
* Returns a Keyword with the given namespace and name.  Do not use :
* in the keyword strings, it will be added automatically.
*/
cljs.core.keyword = (function() {
var keyword = null;
var keyword__1 = (function (name){
if(cljs.core.keyword_QMARK_.call(null,name))
{return name;
} else
{if(cljs.core.symbol_QMARK_.call(null,name))
{return cljs.core.str_STAR_.call(null,"\uFDD0","'",cljs.core.subs.call(null,name,2));
} else
{if("\uFDD0'else")
{return cljs.core.str_STAR_.call(null,"\uFDD0","'",name);
} else
{return null;
}
}
}
});
var keyword__2 = (function (ns,name){
return keyword.call(null,cljs.core.str_STAR_.call(null,ns,"/",name));
});
keyword = function(ns,name){
switch(arguments.length){
case 1:
return keyword__1.call(this,ns);
case 2:
return keyword__2.call(this,ns,name);
}
throw('Invalid arity: ' + arguments.length);
};
keyword.cljs$lang$arity$1 = keyword__1;
keyword.cljs$lang$arity$2 = keyword__2;
return keyword;
})()
;
/**
* Assumes x is sequential. Returns true if x equals y, otherwise
* returns false.
*/
cljs.core.equiv_sequential = (function equiv_sequential(x,y){
return cljs.core.boolean$.call(null,((cljs.core.sequential_QMARK_.call(null,y))?(function (){var xs__7302 = cljs.core.seq.call(null,x);
var ys__7303 = cljs.core.seq.call(null,y);
while(true){
if((xs__7302 == null))
{return (ys__7303 == null);
} else
{if((ys__7303 == null))
{return false;
} else
{if(cljs.core._EQ_.call(null,cljs.core.first.call(null,xs__7302),cljs.core.first.call(null,ys__7303)))
{{
var G__7304 = cljs.core.next.call(null,xs__7302);
var G__7305 = cljs.core.next.call(null,ys__7303);
xs__7302 = G__7304;
ys__7303 = G__7305;
continue;
}
} else
{if("\uFDD0'else")
{return false;
} else
{return null;
}
}
}
}
break;
}
})():null));
});
cljs.core.hash_combine = (function hash_combine(seed,hash){
return (seed ^ (((hash + 2654435769) + (seed << 6)) + (seed >> 2)));
});
cljs.core.hash_coll = (function hash_coll(coll){
return cljs.core.reduce.call(null,(function (p1__7306_SHARP_,p2__7307_SHARP_){
return cljs.core.hash_combine.call(null,p1__7306_SHARP_,cljs.core.hash.call(null,p2__7307_SHARP_,false));
}),cljs.core.hash.call(null,cljs.core.first.call(null,coll),false),cljs.core.next.call(null,coll));
});
cljs.core.hash_imap = (function hash_imap(m){
var h__7311 = 0;
var s__7312 = cljs.core.seq.call(null,m);
while(true){
if(s__7312)
{var e__7313 = cljs.core.first.call(null,s__7312);
{
var G__7314 = ((h__7311 + (cljs.core.hash.call(null,cljs.core.key.call(null,e__7313)) ^ cljs.core.hash.call(null,cljs.core.val.call(null,e__7313)))) % 4503599627370496);
var G__7315 = cljs.core.next.call(null,s__7312);
h__7311 = G__7314;
s__7312 = G__7315;
continue;
}
} else
{return h__7311;
}
break;
}
});
cljs.core.hash_iset = (function hash_iset(s){
var h__7319 = 0;
var s__7320 = cljs.core.seq.call(null,s);
while(true){
if(s__7320)
{var e__7321 = cljs.core.first.call(null,s__7320);
{
var G__7322 = ((h__7319 + cljs.core.hash.call(null,e__7321)) % 4503599627370496);
var G__7323 = cljs.core.next.call(null,s__7320);
h__7319 = G__7322;
s__7320 = G__7323;
continue;
}
} else
{return h__7319;
}
break;
}
});
/**
* Takes a JavaScript object and a map of names to functions and
* attaches said functions as methods on the object.  Any references to
* JavaScript's implict this (via the this-as macro) will resolve to the
* object that the function is attached.
*/
cljs.core.extend_object_BANG_ = (function extend_object_BANG_(obj,fn_map){
var G__7344__7345 = cljs.core.seq.call(null,fn_map);
if(G__7344__7345)
{var G__7347__7349 = cljs.core.first.call(null,G__7344__7345);
var vec__7348__7350 = G__7347__7349;
var key_name__7351 = cljs.core.nth.call(null,vec__7348__7350,0,null);
var f__7352 = cljs.core.nth.call(null,vec__7348__7350,1,null);
var G__7344__7353 = G__7344__7345;
var G__7347__7354 = G__7347__7349;
var G__7344__7355 = G__7344__7353;
while(true){
var vec__7356__7357 = G__7347__7354;
var key_name__7358 = cljs.core.nth.call(null,vec__7356__7357,0,null);
var f__7359 = cljs.core.nth.call(null,vec__7356__7357,1,null);
var G__7344__7360 = G__7344__7355;
var str_name__7361 = cljs.core.name.call(null,key_name__7358);
(obj[str_name__7361] = f__7359);
var temp__3974__auto____7362 = cljs.core.next.call(null,G__7344__7360);
if(temp__3974__auto____7362)
{var G__7344__7363 = temp__3974__auto____7362;
{
var G__7364 = cljs.core.first.call(null,G__7344__7363);
var G__7365 = G__7344__7363;
G__7347__7354 = G__7364;
G__7344__7355 = G__7365;
continue;
}
} else
{}
break;
}
} else
{}
return obj;
});

/**
* @constructor
*/
cljs.core.List = (function (meta,first,rest,count,__hash){
this.meta = meta;
this.first = first;
this.rest = rest;
this.count = count;
this.__hash = __hash;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 65413358;
})
cljs.core.List.cljs$lang$type = true;
cljs.core.List.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/List");
});
cljs.core.List.prototype.cljs$core$IHash$_hash$arity$1 = (function (coll){
var this__7366 = this;
var h__2220__auto____7367 = this__7366.__hash;
if(!((h__2220__auto____7367 == null)))
{return h__2220__auto____7367;
} else
{var h__2220__auto____7368 = cljs.core.hash_coll.call(null,coll);
this__7366.__hash = h__2220__auto____7368;
return h__2220__auto____7368;
}
});
cljs.core.List.prototype.cljs$core$INext$_next$arity$1 = (function (coll){
var this__7369 = this;
if((this__7369.count === 1))
{return null;
} else
{return this__7369.rest;
}
});
cljs.core.List.prototype.cljs$core$ICollection$_conj$arity$2 = (function (coll,o){
var this__7370 = this;
return (new cljs.core.List(this__7370.meta,o,coll,(this__7370.count + 1),null));
});
cljs.core.List.prototype.toString = (function (){
var this__7371 = this;
var this__7372 = this;
return cljs.core.pr_str.call(null,this__7372);
});
cljs.core.List.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (coll){
var this__7373 = this;
return coll;
});
cljs.core.List.prototype.cljs$core$ICounted$_count$arity$1 = (function (coll){
var this__7374 = this;
return this__7374.count;
});
cljs.core.List.prototype.cljs$core$IStack$_peek$arity$1 = (function (coll){
var this__7375 = this;
return this__7375.first;
});
cljs.core.List.prototype.cljs$core$IStack$_pop$arity$1 = (function (coll){
var this__7376 = this;
return coll.cljs$core$ISeq$_rest$arity$1(coll);
});
cljs.core.List.prototype.cljs$core$ISeq$_first$arity$1 = (function (coll){
var this__7377 = this;
return this__7377.first;
});
cljs.core.List.prototype.cljs$core$ISeq$_rest$arity$1 = (function (coll){
var this__7378 = this;
if((this__7378.count === 1))
{return cljs.core.List.EMPTY;
} else
{return this__7378.rest;
}
});
cljs.core.List.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (coll,other){
var this__7379 = this;
return cljs.core.equiv_sequential.call(null,coll,other);
});
cljs.core.List.prototype.cljs$core$IWithMeta$_with_meta$arity$2 = (function (coll,meta){
var this__7380 = this;
return (new cljs.core.List(meta,this__7380.first,this__7380.rest,this__7380.count,this__7380.__hash));
});
cljs.core.List.prototype.cljs$core$IMeta$_meta$arity$1 = (function (coll){
var this__7381 = this;
return this__7381.meta;
});
cljs.core.List.prototype.cljs$core$IEmptyableCollection$_empty$arity$1 = (function (coll){
var this__7382 = this;
return cljs.core.List.EMPTY;
});
cljs.core.List;

/**
* @constructor
*/
cljs.core.EmptyList = (function (meta){
this.meta = meta;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 65413326;
})
cljs.core.EmptyList.cljs$lang$type = true;
cljs.core.EmptyList.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/EmptyList");
});
cljs.core.EmptyList.prototype.cljs$core$IHash$_hash$arity$1 = (function (coll){
var this__7383 = this;
return 0;
});
cljs.core.EmptyList.prototype.cljs$core$INext$_next$arity$1 = (function (coll){
var this__7384 = this;
return null;
});
cljs.core.EmptyList.prototype.cljs$core$ICollection$_conj$arity$2 = (function (coll,o){
var this__7385 = this;
return (new cljs.core.List(this__7385.meta,o,null,1,null));
});
cljs.core.EmptyList.prototype.toString = (function (){
var this__7386 = this;
var this__7387 = this;
return cljs.core.pr_str.call(null,this__7387);
});
cljs.core.EmptyList.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (coll){
var this__7388 = this;
return null;
});
cljs.core.EmptyList.prototype.cljs$core$ICounted$_count$arity$1 = (function (coll){
var this__7389 = this;
return 0;
});
cljs.core.EmptyList.prototype.cljs$core$IStack$_peek$arity$1 = (function (coll){
var this__7390 = this;
return null;
});
cljs.core.EmptyList.prototype.cljs$core$IStack$_pop$arity$1 = (function (coll){
var this__7391 = this;
throw (new Error("Can't pop empty list"));
});
cljs.core.EmptyList.prototype.cljs$core$ISeq$_first$arity$1 = (function (coll){
var this__7392 = this;
return null;
});
cljs.core.EmptyList.prototype.cljs$core$ISeq$_rest$arity$1 = (function (coll){
var this__7393 = this;
return cljs.core.List.EMPTY;
});
cljs.core.EmptyList.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (coll,other){
var this__7394 = this;
return cljs.core.equiv_sequential.call(null,coll,other);
});
cljs.core.EmptyList.prototype.cljs$core$IWithMeta$_with_meta$arity$2 = (function (coll,meta){
var this__7395 = this;
return (new cljs.core.EmptyList(meta));
});
cljs.core.EmptyList.prototype.cljs$core$IMeta$_meta$arity$1 = (function (coll){
var this__7396 = this;
return this__7396.meta;
});
cljs.core.EmptyList.prototype.cljs$core$IEmptyableCollection$_empty$arity$1 = (function (coll){
var this__7397 = this;
return coll;
});
cljs.core.EmptyList;
cljs.core.List.EMPTY = (new cljs.core.EmptyList(null));
cljs.core.reversible_QMARK_ = (function reversible_QMARK_(coll){
var G__7401__7402 = coll;
if(G__7401__7402)
{if((function (){var or__3824__auto____7403 = (G__7401__7402.cljs$lang$protocol_mask$partition0$ & 134217728);
if(or__3824__auto____7403)
{return or__3824__auto____7403;
} else
{return G__7401__7402.cljs$core$IReversible$;
}
})())
{return true;
} else
{if((!G__7401__7402.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.IReversible,G__7401__7402);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.IReversible,G__7401__7402);
}
});
cljs.core.rseq = (function rseq(coll){
return cljs.core._rseq.call(null,coll);
});
/**
* Returns a seq of the items in coll in reverse order. Not lazy.
*/
cljs.core.reverse = (function reverse(coll){
if(cljs.core.reversible_QMARK_.call(null,coll))
{return cljs.core.rseq.call(null,coll);
} else
{return cljs.core.reduce.call(null,cljs.core.conj,cljs.core.List.EMPTY,coll);
}
});
/**
* @param {...*} var_args
*/
cljs.core.list = (function() {
var list = null;
var list__0 = (function (){
return cljs.core.List.EMPTY;
});
var list__1 = (function (x){
return cljs.core.conj.call(null,cljs.core.List.EMPTY,x);
});
var list__2 = (function (x,y){
return cljs.core.conj.call(null,list.call(null,y),x);
});
var list__3 = (function (x,y,z){
return cljs.core.conj.call(null,list.call(null,y,z),x);
});
var list__4 = (function() { 
var G__7404__delegate = function (x,y,z,items){
return cljs.core.conj.call(null,cljs.core.conj.call(null,cljs.core.conj.call(null,cljs.core.reduce.call(null,cljs.core.conj,cljs.core.List.EMPTY,cljs.core.reverse.call(null,items)),z),y),x);
};
var G__7404 = function (x,y,z,var_args){
var items = null;
if (goog.isDef(var_args)) {
  items = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return G__7404__delegate.call(this, x, y, z, items);
};
G__7404.cljs$lang$maxFixedArity = 3;
G__7404.cljs$lang$applyTo = (function (arglist__7405){
var x = cljs.core.first(arglist__7405);
var y = cljs.core.first(cljs.core.next(arglist__7405));
var z = cljs.core.first(cljs.core.next(cljs.core.next(arglist__7405)));
var items = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__7405)));
return G__7404__delegate(x, y, z, items);
});
G__7404.cljs$lang$arity$variadic = G__7404__delegate;
return G__7404;
})()
;
list = function(x,y,z,var_args){
var items = var_args;
switch(arguments.length){
case 0:
return list__0.call(this);
case 1:
return list__1.call(this,x);
case 2:
return list__2.call(this,x,y);
case 3:
return list__3.call(this,x,y,z);
default:
return list__4.cljs$lang$arity$variadic(x,y,z, cljs.core.array_seq(arguments, 3));
}
throw('Invalid arity: ' + arguments.length);
};
list.cljs$lang$maxFixedArity = 3;
list.cljs$lang$applyTo = list__4.cljs$lang$applyTo;
list.cljs$lang$arity$0 = list__0;
list.cljs$lang$arity$1 = list__1;
list.cljs$lang$arity$2 = list__2;
list.cljs$lang$arity$3 = list__3;
list.cljs$lang$arity$variadic = list__4.cljs$lang$arity$variadic;
return list;
})()
;

/**
* @constructor
*/
cljs.core.Cons = (function (meta,first,rest,__hash){
this.meta = meta;
this.first = first;
this.rest = rest;
this.__hash = __hash;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 65405164;
})
cljs.core.Cons.cljs$lang$type = true;
cljs.core.Cons.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/Cons");
});
cljs.core.Cons.prototype.cljs$core$IHash$_hash$arity$1 = (function (coll){
var this__7406 = this;
var h__2220__auto____7407 = this__7406.__hash;
if(!((h__2220__auto____7407 == null)))
{return h__2220__auto____7407;
} else
{var h__2220__auto____7408 = cljs.core.hash_coll.call(null,coll);
this__7406.__hash = h__2220__auto____7408;
return h__2220__auto____7408;
}
});
cljs.core.Cons.prototype.cljs$core$INext$_next$arity$1 = (function (coll){
var this__7409 = this;
if((this__7409.rest == null))
{return null;
} else
{return cljs.core._seq.call(null,this__7409.rest);
}
});
cljs.core.Cons.prototype.cljs$core$ICollection$_conj$arity$2 = (function (coll,o){
var this__7410 = this;
return (new cljs.core.Cons(null,o,coll,this__7410.__hash));
});
cljs.core.Cons.prototype.toString = (function (){
var this__7411 = this;
var this__7412 = this;
return cljs.core.pr_str.call(null,this__7412);
});
cljs.core.Cons.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (coll){
var this__7413 = this;
return coll;
});
cljs.core.Cons.prototype.cljs$core$ISeq$_first$arity$1 = (function (coll){
var this__7414 = this;
return this__7414.first;
});
cljs.core.Cons.prototype.cljs$core$ISeq$_rest$arity$1 = (function (coll){
var this__7415 = this;
if((this__7415.rest == null))
{return cljs.core.List.EMPTY;
} else
{return this__7415.rest;
}
});
cljs.core.Cons.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (coll,other){
var this__7416 = this;
return cljs.core.equiv_sequential.call(null,coll,other);
});
cljs.core.Cons.prototype.cljs$core$IWithMeta$_with_meta$arity$2 = (function (coll,meta){
var this__7417 = this;
return (new cljs.core.Cons(meta,this__7417.first,this__7417.rest,this__7417.__hash));
});
cljs.core.Cons.prototype.cljs$core$IMeta$_meta$arity$1 = (function (coll){
var this__7418 = this;
return this__7418.meta;
});
cljs.core.Cons.prototype.cljs$core$IEmptyableCollection$_empty$arity$1 = (function (coll){
var this__7419 = this;
return cljs.core.with_meta.call(null,cljs.core.List.EMPTY,this__7419.meta);
});
cljs.core.Cons;
/**
* Returns a new seq where x is the first element and seq is the rest.
*/
cljs.core.cons = (function cons(x,coll){
if((function (){var or__3824__auto____7424 = (coll == null);
if(or__3824__auto____7424)
{return or__3824__auto____7424;
} else
{var G__7425__7426 = coll;
if(G__7425__7426)
{if((function (){var or__3824__auto____7427 = (G__7425__7426.cljs$lang$protocol_mask$partition0$ & 64);
if(or__3824__auto____7427)
{return or__3824__auto____7427;
} else
{return G__7425__7426.cljs$core$ISeq$;
}
})())
{return true;
} else
{if((!G__7425__7426.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.ISeq,G__7425__7426);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.ISeq,G__7425__7426);
}
}
})())
{return (new cljs.core.Cons(null,x,coll,null));
} else
{return (new cljs.core.Cons(null,x,cljs.core.seq.call(null,coll),null));
}
});
cljs.core.list_QMARK_ = (function list_QMARK_(x){
var G__7431__7432 = x;
if(G__7431__7432)
{if((function (){var or__3824__auto____7433 = (G__7431__7432.cljs$lang$protocol_mask$partition0$ & 33554432);
if(or__3824__auto____7433)
{return or__3824__auto____7433;
} else
{return G__7431__7432.cljs$core$IList$;
}
})())
{return true;
} else
{if((!G__7431__7432.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.IList,G__7431__7432);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.IList,G__7431__7432);
}
});
(cljs.core.IReduce["string"] = true);
(cljs.core._reduce["string"] = (function() {
var G__7434 = null;
var G__7434__2 = (function (string,f){
return cljs.core.ci_reduce.call(null,string,f);
});
var G__7434__3 = (function (string,f,start){
return cljs.core.ci_reduce.call(null,string,f,start);
});
G__7434 = function(string,f,start){
switch(arguments.length){
case 2:
return G__7434__2.call(this,string,f);
case 3:
return G__7434__3.call(this,string,f,start);
}
throw('Invalid arity: ' + arguments.length);
};
return G__7434;
})()
);
(cljs.core.ILookup["string"] = true);
(cljs.core._lookup["string"] = (function() {
var G__7435 = null;
var G__7435__2 = (function (string,k){
return cljs.core._nth.call(null,string,k);
});
var G__7435__3 = (function (string,k,not_found){
return cljs.core._nth.call(null,string,k,not_found);
});
G__7435 = function(string,k,not_found){
switch(arguments.length){
case 2:
return G__7435__2.call(this,string,k);
case 3:
return G__7435__3.call(this,string,k,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
return G__7435;
})()
);
(cljs.core.IIndexed["string"] = true);
(cljs.core._nth["string"] = (function() {
var G__7436 = null;
var G__7436__2 = (function (string,n){
if((n < cljs.core._count.call(null,string)))
{return string.charAt(n);
} else
{return null;
}
});
var G__7436__3 = (function (string,n,not_found){
if((n < cljs.core._count.call(null,string)))
{return string.charAt(n);
} else
{return not_found;
}
});
G__7436 = function(string,n,not_found){
switch(arguments.length){
case 2:
return G__7436__2.call(this,string,n);
case 3:
return G__7436__3.call(this,string,n,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
return G__7436;
})()
);
(cljs.core.ICounted["string"] = true);
(cljs.core._count["string"] = (function (s){
return s.length;
}));
(cljs.core.ISeqable["string"] = true);
(cljs.core._seq["string"] = (function (string){
return cljs.core.prim_seq.call(null,string,0);
}));
(cljs.core.IHash["string"] = true);
(cljs.core._hash["string"] = (function (o){
return goog.string.hashCode(o);
}));

/**
* @constructor
*/
cljs.core.Keyword = (function (k){
this.k = k;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 1;
})
cljs.core.Keyword.cljs$lang$type = true;
cljs.core.Keyword.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/Keyword");
});
cljs.core.Keyword.prototype.call = (function() {
var G__7448 = null;
var G__7448__2 = (function (this_sym7439,coll){
var this__7441 = this;
var this_sym7439__7442 = this;
var ___7443 = this_sym7439__7442;
if((coll == null))
{return null;
} else
{var strobj__7444 = coll.strobj;
if((strobj__7444 == null))
{return cljs.core._lookup.call(null,coll,this__7441.k,null);
} else
{return (strobj__7444[this__7441.k]);
}
}
});
var G__7448__3 = (function (this_sym7440,coll,not_found){
var this__7441 = this;
var this_sym7440__7445 = this;
var ___7446 = this_sym7440__7445;
if((coll == null))
{return not_found;
} else
{return cljs.core._lookup.call(null,coll,this__7441.k,not_found);
}
});
G__7448 = function(this_sym7440,coll,not_found){
switch(arguments.length){
case 2:
return G__7448__2.call(this,this_sym7440,coll);
case 3:
return G__7448__3.call(this,this_sym7440,coll,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
return G__7448;
})()
;
cljs.core.Keyword.prototype.apply = (function (this_sym7437,args7438){
var this__7447 = this;
return this_sym7437.call.apply(this_sym7437,[this_sym7437].concat(args7438.slice()));
});
cljs.core.Keyword;
String.prototype.cljs$core$IFn$ = true;
String.prototype.call = (function() {
var G__7457 = null;
var G__7457__2 = (function (this_sym7451,coll){
var this_sym7451__7453 = this;
var this__7454 = this_sym7451__7453;
return cljs.core._lookup.call(null,coll,this__7454.toString(),null);
});
var G__7457__3 = (function (this_sym7452,coll,not_found){
var this_sym7452__7455 = this;
var this__7456 = this_sym7452__7455;
return cljs.core._lookup.call(null,coll,this__7456.toString(),not_found);
});
G__7457 = function(this_sym7452,coll,not_found){
switch(arguments.length){
case 2:
return G__7457__2.call(this,this_sym7452,coll);
case 3:
return G__7457__3.call(this,this_sym7452,coll,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
return G__7457;
})()
;
String.prototype.apply = (function (this_sym7449,args7450){
return this_sym7449.call.apply(this_sym7449,[this_sym7449].concat(args7450.slice()));
});
String.prototype.apply = (function (s,args){
if((cljs.core.count.call(null,args) < 2))
{return cljs.core._lookup.call(null,(args[0]),s,null);
} else
{return cljs.core._lookup.call(null,(args[0]),s,(args[1]));
}
});
cljs.core.lazy_seq_value = (function lazy_seq_value(lazy_seq){
var x__7459 = lazy_seq.x;
if(lazy_seq.realized)
{return x__7459;
} else
{lazy_seq.x = x__7459.call(null);
lazy_seq.realized = true;
return lazy_seq.x;
}
});

/**
* @constructor
*/
cljs.core.LazySeq = (function (meta,realized,x,__hash){
this.meta = meta;
this.realized = realized;
this.x = x;
this.__hash = __hash;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 31850700;
})
cljs.core.LazySeq.cljs$lang$type = true;
cljs.core.LazySeq.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/LazySeq");
});
cljs.core.LazySeq.prototype.cljs$core$IHash$_hash$arity$1 = (function (coll){
var this__7460 = this;
var h__2220__auto____7461 = this__7460.__hash;
if(!((h__2220__auto____7461 == null)))
{return h__2220__auto____7461;
} else
{var h__2220__auto____7462 = cljs.core.hash_coll.call(null,coll);
this__7460.__hash = h__2220__auto____7462;
return h__2220__auto____7462;
}
});
cljs.core.LazySeq.prototype.cljs$core$INext$_next$arity$1 = (function (coll){
var this__7463 = this;
return cljs.core._seq.call(null,coll.cljs$core$ISeq$_rest$arity$1(coll));
});
cljs.core.LazySeq.prototype.cljs$core$ICollection$_conj$arity$2 = (function (coll,o){
var this__7464 = this;
return cljs.core.cons.call(null,o,coll);
});
cljs.core.LazySeq.prototype.toString = (function (){
var this__7465 = this;
var this__7466 = this;
return cljs.core.pr_str.call(null,this__7466);
});
cljs.core.LazySeq.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (coll){
var this__7467 = this;
return cljs.core.seq.call(null,cljs.core.lazy_seq_value.call(null,coll));
});
cljs.core.LazySeq.prototype.cljs$core$ISeq$_first$arity$1 = (function (coll){
var this__7468 = this;
return cljs.core.first.call(null,cljs.core.lazy_seq_value.call(null,coll));
});
cljs.core.LazySeq.prototype.cljs$core$ISeq$_rest$arity$1 = (function (coll){
var this__7469 = this;
return cljs.core.rest.call(null,cljs.core.lazy_seq_value.call(null,coll));
});
cljs.core.LazySeq.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (coll,other){
var this__7470 = this;
return cljs.core.equiv_sequential.call(null,coll,other);
});
cljs.core.LazySeq.prototype.cljs$core$IWithMeta$_with_meta$arity$2 = (function (coll,meta){
var this__7471 = this;
return (new cljs.core.LazySeq(meta,this__7471.realized,this__7471.x,this__7471.__hash));
});
cljs.core.LazySeq.prototype.cljs$core$IMeta$_meta$arity$1 = (function (coll){
var this__7472 = this;
return this__7472.meta;
});
cljs.core.LazySeq.prototype.cljs$core$IEmptyableCollection$_empty$arity$1 = (function (coll){
var this__7473 = this;
return cljs.core.with_meta.call(null,cljs.core.List.EMPTY,this__7473.meta);
});
cljs.core.LazySeq;

/**
* @constructor
*/
cljs.core.ChunkBuffer = (function (buf,end){
this.buf = buf;
this.end = end;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 2;
})
cljs.core.ChunkBuffer.cljs$lang$type = true;
cljs.core.ChunkBuffer.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/ChunkBuffer");
});
cljs.core.ChunkBuffer.prototype.cljs$core$ICounted$_count$arity$1 = (function (_){
var this__7474 = this;
return this__7474.end;
});
cljs.core.ChunkBuffer.prototype.add = (function (o){
var this__7475 = this;
var ___7476 = this;
(this__7475.buf[this__7475.end] = o);
return this__7475.end = (this__7475.end + 1);
});
cljs.core.ChunkBuffer.prototype.chunk = (function (o){
var this__7477 = this;
var ___7478 = this;
var ret__7479 = (new cljs.core.ArrayChunk(this__7477.buf,0,this__7477.end));
this__7477.buf = null;
return ret__7479;
});
cljs.core.ChunkBuffer;
cljs.core.chunk_buffer = (function chunk_buffer(capacity){
return (new cljs.core.ChunkBuffer(cljs.core.make_array.call(null,capacity),0));
});

/**
* @constructor
*/
cljs.core.ArrayChunk = (function (arr,off,end){
this.arr = arr;
this.off = off;
this.end = end;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 524306;
})
cljs.core.ArrayChunk.cljs$lang$type = true;
cljs.core.ArrayChunk.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/ArrayChunk");
});
cljs.core.ArrayChunk.prototype.cljs$core$IReduce$_reduce$arity$2 = (function (coll,f){
var this__7480 = this;
return cljs.core.ci_reduce.call(null,coll,f,(this__7480.arr[this__7480.off]),(this__7480.off + 1));
});
cljs.core.ArrayChunk.prototype.cljs$core$IReduce$_reduce$arity$3 = (function (coll,f,start){
var this__7481 = this;
return cljs.core.ci_reduce.call(null,coll,f,start,this__7481.off);
});
cljs.core.ArrayChunk.prototype.cljs$core$IChunk$ = true;
cljs.core.ArrayChunk.prototype.cljs$core$IChunk$_drop_first$arity$1 = (function (coll){
var this__7482 = this;
if((this__7482.off === this__7482.end))
{throw (new Error("-drop-first of empty chunk"));
} else
{return (new cljs.core.ArrayChunk(this__7482.arr,(this__7482.off + 1),this__7482.end));
}
});
cljs.core.ArrayChunk.prototype.cljs$core$IIndexed$_nth$arity$2 = (function (coll,i){
var this__7483 = this;
return (this__7483.arr[(this__7483.off + i)]);
});
cljs.core.ArrayChunk.prototype.cljs$core$IIndexed$_nth$arity$3 = (function (coll,i,not_found){
var this__7484 = this;
if((function (){var and__3822__auto____7485 = (i >= 0);
if(and__3822__auto____7485)
{return (i < (this__7484.end - this__7484.off));
} else
{return and__3822__auto____7485;
}
})())
{return (this__7484.arr[(this__7484.off + i)]);
} else
{return not_found;
}
});
cljs.core.ArrayChunk.prototype.cljs$core$ICounted$_count$arity$1 = (function (_){
var this__7486 = this;
return (this__7486.end - this__7486.off);
});
cljs.core.ArrayChunk;
cljs.core.array_chunk = (function() {
var array_chunk = null;
var array_chunk__1 = (function (arr){
return array_chunk.call(null,arr,0,arr.length);
});
var array_chunk__2 = (function (arr,off){
return array_chunk.call(null,arr,off,arr.length);
});
var array_chunk__3 = (function (arr,off,end){
return (new cljs.core.ArrayChunk(arr,off,end));
});
array_chunk = function(arr,off,end){
switch(arguments.length){
case 1:
return array_chunk__1.call(this,arr);
case 2:
return array_chunk__2.call(this,arr,off);
case 3:
return array_chunk__3.call(this,arr,off,end);
}
throw('Invalid arity: ' + arguments.length);
};
array_chunk.cljs$lang$arity$1 = array_chunk__1;
array_chunk.cljs$lang$arity$2 = array_chunk__2;
array_chunk.cljs$lang$arity$3 = array_chunk__3;
return array_chunk;
})()
;

/**
* @constructor
*/
cljs.core.ChunkedCons = (function (chunk,more,meta){
this.chunk = chunk;
this.more = more;
this.meta = meta;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 27656296;
})
cljs.core.ChunkedCons.cljs$lang$type = true;
cljs.core.ChunkedCons.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/ChunkedCons");
});
cljs.core.ChunkedCons.prototype.cljs$core$ICollection$_conj$arity$2 = (function (this$,o){
var this__7487 = this;
return cljs.core.cons.call(null,o,this$);
});
cljs.core.ChunkedCons.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (coll){
var this__7488 = this;
return coll;
});
cljs.core.ChunkedCons.prototype.cljs$core$ISeq$_first$arity$1 = (function (coll){
var this__7489 = this;
return cljs.core._nth.call(null,this__7489.chunk,0);
});
cljs.core.ChunkedCons.prototype.cljs$core$ISeq$_rest$arity$1 = (function (coll){
var this__7490 = this;
if((cljs.core._count.call(null,this__7490.chunk) > 1))
{return (new cljs.core.ChunkedCons(cljs.core._drop_first.call(null,this__7490.chunk),this__7490.more,this__7490.meta));
} else
{if((this__7490.more == null))
{return cljs.core.List.EMPTY;
} else
{return this__7490.more;
}
}
});
cljs.core.ChunkedCons.prototype.cljs$core$IChunkedNext$ = true;
cljs.core.ChunkedCons.prototype.cljs$core$IChunkedNext$_chunked_next$arity$1 = (function (coll){
var this__7491 = this;
if((this__7491.more == null))
{return null;
} else
{return this__7491.more;
}
});
cljs.core.ChunkedCons.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (coll,other){
var this__7492 = this;
return cljs.core.equiv_sequential.call(null,coll,other);
});
cljs.core.ChunkedCons.prototype.cljs$core$IWithMeta$_with_meta$arity$2 = (function (coll,m){
var this__7493 = this;
return (new cljs.core.ChunkedCons(this__7493.chunk,this__7493.more,m));
});
cljs.core.ChunkedCons.prototype.cljs$core$IMeta$_meta$arity$1 = (function (coll){
var this__7494 = this;
return this__7494.meta;
});
cljs.core.ChunkedCons.prototype.cljs$core$IChunkedSeq$ = true;
cljs.core.ChunkedCons.prototype.cljs$core$IChunkedSeq$_chunked_first$arity$1 = (function (coll){
var this__7495 = this;
return this__7495.chunk;
});
cljs.core.ChunkedCons.prototype.cljs$core$IChunkedSeq$_chunked_rest$arity$1 = (function (coll){
var this__7496 = this;
if((this__7496.more == null))
{return cljs.core.List.EMPTY;
} else
{return this__7496.more;
}
});
cljs.core.ChunkedCons;
cljs.core.chunk_cons = (function chunk_cons(chunk,rest){
if((cljs.core._count.call(null,chunk) === 0))
{return rest;
} else
{return (new cljs.core.ChunkedCons(chunk,rest,null));
}
});
cljs.core.chunk_append = (function chunk_append(b,x){
return b.add(x);
});
cljs.core.chunk = (function chunk(b){
return b.chunk();
});
cljs.core.chunk_first = (function chunk_first(s){
return cljs.core._chunked_first.call(null,s);
});
cljs.core.chunk_rest = (function chunk_rest(s){
return cljs.core._chunked_rest.call(null,s);
});
cljs.core.chunk_next = (function chunk_next(s){
if((function (){var G__7500__7501 = s;
if(G__7500__7501)
{if(cljs.core.truth_((function (){var or__3824__auto____7502 = null;
if(cljs.core.truth_(or__3824__auto____7502))
{return or__3824__auto____7502;
} else
{return G__7500__7501.cljs$core$IChunkedNext$;
}
})()))
{return true;
} else
{if((!G__7500__7501.cljs$lang$protocol_mask$partition$))
{return cljs.core.type_satisfies_.call(null,cljs.core.IChunkedNext,G__7500__7501);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.IChunkedNext,G__7500__7501);
}
})())
{return cljs.core._chunked_next.call(null,s);
} else
{return cljs.core.seq.call(null,cljs.core._chunked_rest.call(null,s));
}
});
/**
* Naive impl of to-array as a start.
*/
cljs.core.to_array = (function to_array(s){
var ary__7505 = [];
var s__7506 = s;
while(true){
if(cljs.core.seq.call(null,s__7506))
{ary__7505.push(cljs.core.first.call(null,s__7506));
{
var G__7507 = cljs.core.next.call(null,s__7506);
s__7506 = G__7507;
continue;
}
} else
{return ary__7505;
}
break;
}
});
/**
* Returns a (potentially-ragged) 2-dimensional array
* containing the contents of coll.
*/
cljs.core.to_array_2d = (function to_array_2d(coll){
var ret__7511 = cljs.core.make_array.call(null,cljs.core.count.call(null,coll));
var i__7512 = 0;
var xs__7513 = cljs.core.seq.call(null,coll);
while(true){
if(xs__7513)
{(ret__7511[i__7512] = cljs.core.to_array.call(null,cljs.core.first.call(null,xs__7513)));
{
var G__7514 = (i__7512 + 1);
var G__7515 = cljs.core.next.call(null,xs__7513);
i__7512 = G__7514;
xs__7513 = G__7515;
continue;
}
} else
{}
break;
}
return ret__7511;
});
cljs.core.long_array = (function() {
var long_array = null;
var long_array__1 = (function (size_or_seq){
if(cljs.core.number_QMARK_.call(null,size_or_seq))
{return long_array.call(null,size_or_seq,null);
} else
{if(cljs.core.seq_QMARK_.call(null,size_or_seq))
{return cljs.core.into_array.call(null,size_or_seq);
} else
{if("\uFDD0'else")
{throw (new Error("long-array called with something other than size or ISeq"));
} else
{return null;
}
}
}
});
var long_array__2 = (function (size,init_val_or_seq){
var a__7523 = cljs.core.make_array.call(null,size);
if(cljs.core.seq_QMARK_.call(null,init_val_or_seq))
{var s__7524 = cljs.core.seq.call(null,init_val_or_seq);
var i__7525 = 0;
var s__7526 = s__7524;
while(true){
if(cljs.core.truth_((function (){var and__3822__auto____7527 = s__7526;
if(and__3822__auto____7527)
{return (i__7525 < size);
} else
{return and__3822__auto____7527;
}
})()))
{(a__7523[i__7525] = cljs.core.first.call(null,s__7526));
{
var G__7530 = (i__7525 + 1);
var G__7531 = cljs.core.next.call(null,s__7526);
i__7525 = G__7530;
s__7526 = G__7531;
continue;
}
} else
{return a__7523;
}
break;
}
} else
{var n__2555__auto____7528 = size;
var i__7529 = 0;
while(true){
if((i__7529 < n__2555__auto____7528))
{(a__7523[i__7529] = init_val_or_seq);
{
var G__7532 = (i__7529 + 1);
i__7529 = G__7532;
continue;
}
} else
{}
break;
}
return a__7523;
}
});
long_array = function(size,init_val_or_seq){
switch(arguments.length){
case 1:
return long_array__1.call(this,size);
case 2:
return long_array__2.call(this,size,init_val_or_seq);
}
throw('Invalid arity: ' + arguments.length);
};
long_array.cljs$lang$arity$1 = long_array__1;
long_array.cljs$lang$arity$2 = long_array__2;
return long_array;
})()
;
cljs.core.double_array = (function() {
var double_array = null;
var double_array__1 = (function (size_or_seq){
if(cljs.core.number_QMARK_.call(null,size_or_seq))
{return double_array.call(null,size_or_seq,null);
} else
{if(cljs.core.seq_QMARK_.call(null,size_or_seq))
{return cljs.core.into_array.call(null,size_or_seq);
} else
{if("\uFDD0'else")
{throw (new Error("double-array called with something other than size or ISeq"));
} else
{return null;
}
}
}
});
var double_array__2 = (function (size,init_val_or_seq){
var a__7540 = cljs.core.make_array.call(null,size);
if(cljs.core.seq_QMARK_.call(null,init_val_or_seq))
{var s__7541 = cljs.core.seq.call(null,init_val_or_seq);
var i__7542 = 0;
var s__7543 = s__7541;
while(true){
if(cljs.core.truth_((function (){var and__3822__auto____7544 = s__7543;
if(and__3822__auto____7544)
{return (i__7542 < size);
} else
{return and__3822__auto____7544;
}
})()))
{(a__7540[i__7542] = cljs.core.first.call(null,s__7543));
{
var G__7547 = (i__7542 + 1);
var G__7548 = cljs.core.next.call(null,s__7543);
i__7542 = G__7547;
s__7543 = G__7548;
continue;
}
} else
{return a__7540;
}
break;
}
} else
{var n__2555__auto____7545 = size;
var i__7546 = 0;
while(true){
if((i__7546 < n__2555__auto____7545))
{(a__7540[i__7546] = init_val_or_seq);
{
var G__7549 = (i__7546 + 1);
i__7546 = G__7549;
continue;
}
} else
{}
break;
}
return a__7540;
}
});
double_array = function(size,init_val_or_seq){
switch(arguments.length){
case 1:
return double_array__1.call(this,size);
case 2:
return double_array__2.call(this,size,init_val_or_seq);
}
throw('Invalid arity: ' + arguments.length);
};
double_array.cljs$lang$arity$1 = double_array__1;
double_array.cljs$lang$arity$2 = double_array__2;
return double_array;
})()
;
cljs.core.object_array = (function() {
var object_array = null;
var object_array__1 = (function (size_or_seq){
if(cljs.core.number_QMARK_.call(null,size_or_seq))
{return object_array.call(null,size_or_seq,null);
} else
{if(cljs.core.seq_QMARK_.call(null,size_or_seq))
{return cljs.core.into_array.call(null,size_or_seq);
} else
{if("\uFDD0'else")
{throw (new Error("object-array called with something other than size or ISeq"));
} else
{return null;
}
}
}
});
var object_array__2 = (function (size,init_val_or_seq){
var a__7557 = cljs.core.make_array.call(null,size);
if(cljs.core.seq_QMARK_.call(null,init_val_or_seq))
{var s__7558 = cljs.core.seq.call(null,init_val_or_seq);
var i__7559 = 0;
var s__7560 = s__7558;
while(true){
if(cljs.core.truth_((function (){var and__3822__auto____7561 = s__7560;
if(and__3822__auto____7561)
{return (i__7559 < size);
} else
{return and__3822__auto____7561;
}
})()))
{(a__7557[i__7559] = cljs.core.first.call(null,s__7560));
{
var G__7564 = (i__7559 + 1);
var G__7565 = cljs.core.next.call(null,s__7560);
i__7559 = G__7564;
s__7560 = G__7565;
continue;
}
} else
{return a__7557;
}
break;
}
} else
{var n__2555__auto____7562 = size;
var i__7563 = 0;
while(true){
if((i__7563 < n__2555__auto____7562))
{(a__7557[i__7563] = init_val_or_seq);
{
var G__7566 = (i__7563 + 1);
i__7563 = G__7566;
continue;
}
} else
{}
break;
}
return a__7557;
}
});
object_array = function(size,init_val_or_seq){
switch(arguments.length){
case 1:
return object_array__1.call(this,size);
case 2:
return object_array__2.call(this,size,init_val_or_seq);
}
throw('Invalid arity: ' + arguments.length);
};
object_array.cljs$lang$arity$1 = object_array__1;
object_array.cljs$lang$arity$2 = object_array__2;
return object_array;
})()
;
cljs.core.bounded_count = (function bounded_count(s,n){
if(cljs.core.counted_QMARK_.call(null,s))
{return cljs.core.count.call(null,s);
} else
{var s__7571 = s;
var i__7572 = n;
var sum__7573 = 0;
while(true){
if(cljs.core.truth_((function (){var and__3822__auto____7574 = (i__7572 > 0);
if(and__3822__auto____7574)
{return cljs.core.seq.call(null,s__7571);
} else
{return and__3822__auto____7574;
}
})()))
{{
var G__7575 = cljs.core.next.call(null,s__7571);
var G__7576 = (i__7572 - 1);
var G__7577 = (sum__7573 + 1);
s__7571 = G__7575;
i__7572 = G__7576;
sum__7573 = G__7577;
continue;
}
} else
{return sum__7573;
}
break;
}
}
});
cljs.core.spread = (function spread(arglist){
if((arglist == null))
{return null;
} else
{if((cljs.core.next.call(null,arglist) == null))
{return cljs.core.seq.call(null,cljs.core.first.call(null,arglist));
} else
{if("\uFDD0'else")
{return cljs.core.cons.call(null,cljs.core.first.call(null,arglist),spread.call(null,cljs.core.next.call(null,arglist)));
} else
{return null;
}
}
}
});
/**
* Returns a lazy seq representing the concatenation of the elements in the supplied colls.
* @param {...*} var_args
*/
cljs.core.concat = (function() {
var concat = null;
var concat__0 = (function (){
return (new cljs.core.LazySeq(null,false,(function (){
return null;
}),null));
});
var concat__1 = (function (x){
return (new cljs.core.LazySeq(null,false,(function (){
return x;
}),null));
});
var concat__2 = (function (x,y){
return (new cljs.core.LazySeq(null,false,(function (){
var s__7582 = cljs.core.seq.call(null,x);
if(s__7582)
{if(cljs.core.chunked_seq_QMARK_.call(null,s__7582))
{return cljs.core.chunk_cons.call(null,cljs.core.chunk_first.call(null,s__7582),concat.call(null,cljs.core.chunk_rest.call(null,s__7582),y));
} else
{return cljs.core.cons.call(null,cljs.core.first.call(null,s__7582),concat.call(null,cljs.core.rest.call(null,s__7582),y));
}
} else
{return y;
}
}),null));
});
var concat__3 = (function() { 
var G__7586__delegate = function (x,y,zs){
var cat__7585 = (function cat(xys,zs){
return (new cljs.core.LazySeq(null,false,(function (){
var xys__7584 = cljs.core.seq.call(null,xys);
if(xys__7584)
{if(cljs.core.chunked_seq_QMARK_.call(null,xys__7584))
{return cljs.core.chunk_cons.call(null,cljs.core.chunk_first.call(null,xys__7584),cat.call(null,cljs.core.chunk_rest.call(null,xys__7584),zs));
} else
{return cljs.core.cons.call(null,cljs.core.first.call(null,xys__7584),cat.call(null,cljs.core.rest.call(null,xys__7584),zs));
}
} else
{if(cljs.core.truth_(zs))
{return cat.call(null,cljs.core.first.call(null,zs),cljs.core.next.call(null,zs));
} else
{return null;
}
}
}),null));
});
return cat__7585.call(null,concat.call(null,x,y),zs);
};
var G__7586 = function (x,y,var_args){
var zs = null;
if (goog.isDef(var_args)) {
  zs = cljs.core.array_seq(Array.prototype.slice.call(arguments, 2),0);
} 
return G__7586__delegate.call(this, x, y, zs);
};
G__7586.cljs$lang$maxFixedArity = 2;
G__7586.cljs$lang$applyTo = (function (arglist__7587){
var x = cljs.core.first(arglist__7587);
var y = cljs.core.first(cljs.core.next(arglist__7587));
var zs = cljs.core.rest(cljs.core.next(arglist__7587));
return G__7586__delegate(x, y, zs);
});
G__7586.cljs$lang$arity$variadic = G__7586__delegate;
return G__7586;
})()
;
concat = function(x,y,var_args){
var zs = var_args;
switch(arguments.length){
case 0:
return concat__0.call(this);
case 1:
return concat__1.call(this,x);
case 2:
return concat__2.call(this,x,y);
default:
return concat__3.cljs$lang$arity$variadic(x,y, cljs.core.array_seq(arguments, 2));
}
throw('Invalid arity: ' + arguments.length);
};
concat.cljs$lang$maxFixedArity = 2;
concat.cljs$lang$applyTo = concat__3.cljs$lang$applyTo;
concat.cljs$lang$arity$0 = concat__0;
concat.cljs$lang$arity$1 = concat__1;
concat.cljs$lang$arity$2 = concat__2;
concat.cljs$lang$arity$variadic = concat__3.cljs$lang$arity$variadic;
return concat;
})()
;
/**
* Creates a new list containing the items prepended to the rest, the
* last of which will be treated as a sequence.
* @param {...*} var_args
*/
cljs.core.list_STAR_ = (function() {
var list_STAR_ = null;
var list_STAR___1 = (function (args){
return cljs.core.seq.call(null,args);
});
var list_STAR___2 = (function (a,args){
return cljs.core.cons.call(null,a,args);
});
var list_STAR___3 = (function (a,b,args){
return cljs.core.cons.call(null,a,cljs.core.cons.call(null,b,args));
});
var list_STAR___4 = (function (a,b,c,args){
return cljs.core.cons.call(null,a,cljs.core.cons.call(null,b,cljs.core.cons.call(null,c,args)));
});
var list_STAR___5 = (function() { 
var G__7588__delegate = function (a,b,c,d,more){
return cljs.core.cons.call(null,a,cljs.core.cons.call(null,b,cljs.core.cons.call(null,c,cljs.core.cons.call(null,d,cljs.core.spread.call(null,more)))));
};
var G__7588 = function (a,b,c,d,var_args){
var more = null;
if (goog.isDef(var_args)) {
  more = cljs.core.array_seq(Array.prototype.slice.call(arguments, 4),0);
} 
return G__7588__delegate.call(this, a, b, c, d, more);
};
G__7588.cljs$lang$maxFixedArity = 4;
G__7588.cljs$lang$applyTo = (function (arglist__7589){
var a = cljs.core.first(arglist__7589);
var b = cljs.core.first(cljs.core.next(arglist__7589));
var c = cljs.core.first(cljs.core.next(cljs.core.next(arglist__7589)));
var d = cljs.core.first(cljs.core.next(cljs.core.next(cljs.core.next(arglist__7589))));
var more = cljs.core.rest(cljs.core.next(cljs.core.next(cljs.core.next(arglist__7589))));
return G__7588__delegate(a, b, c, d, more);
});
G__7588.cljs$lang$arity$variadic = G__7588__delegate;
return G__7588;
})()
;
list_STAR_ = function(a,b,c,d,var_args){
var more = var_args;
switch(arguments.length){
case 1:
return list_STAR___1.call(this,a);
case 2:
return list_STAR___2.call(this,a,b);
case 3:
return list_STAR___3.call(this,a,b,c);
case 4:
return list_STAR___4.call(this,a,b,c,d);
default:
return list_STAR___5.cljs$lang$arity$variadic(a,b,c,d, cljs.core.array_seq(arguments, 4));
}
throw('Invalid arity: ' + arguments.length);
};
list_STAR_.cljs$lang$maxFixedArity = 4;
list_STAR_.cljs$lang$applyTo = list_STAR___5.cljs$lang$applyTo;
list_STAR_.cljs$lang$arity$1 = list_STAR___1;
list_STAR_.cljs$lang$arity$2 = list_STAR___2;
list_STAR_.cljs$lang$arity$3 = list_STAR___3;
list_STAR_.cljs$lang$arity$4 = list_STAR___4;
list_STAR_.cljs$lang$arity$variadic = list_STAR___5.cljs$lang$arity$variadic;
return list_STAR_;
})()
;
cljs.core.transient$ = (function transient$(coll){
return cljs.core._as_transient.call(null,coll);
});
cljs.core.persistent_BANG_ = (function persistent_BANG_(tcoll){
return cljs.core._persistent_BANG_.call(null,tcoll);
});
cljs.core.conj_BANG_ = (function conj_BANG_(tcoll,val){
return cljs.core._conj_BANG_.call(null,tcoll,val);
});
cljs.core.assoc_BANG_ = (function assoc_BANG_(tcoll,key,val){
return cljs.core._assoc_BANG_.call(null,tcoll,key,val);
});
cljs.core.dissoc_BANG_ = (function dissoc_BANG_(tcoll,key){
return cljs.core._dissoc_BANG_.call(null,tcoll,key);
});
cljs.core.pop_BANG_ = (function pop_BANG_(tcoll){
return cljs.core._pop_BANG_.call(null,tcoll);
});
cljs.core.disj_BANG_ = (function disj_BANG_(tcoll,val){
return cljs.core._disjoin_BANG_.call(null,tcoll,val);
});
cljs.core.apply_to = (function apply_to(f,argc,args){
var args__7631 = cljs.core.seq.call(null,args);
if((argc === 0))
{return f.call(null);
} else
{var a__7632 = cljs.core._first.call(null,args__7631);
var args__7633 = cljs.core._rest.call(null,args__7631);
if((argc === 1))
{if(f.cljs$lang$arity$1)
{return f.cljs$lang$arity$1(a__7632);
} else
{return f.call(null,a__7632);
}
} else
{var b__7634 = cljs.core._first.call(null,args__7633);
var args__7635 = cljs.core._rest.call(null,args__7633);
if((argc === 2))
{if(f.cljs$lang$arity$2)
{return f.cljs$lang$arity$2(a__7632,b__7634);
} else
{return f.call(null,a__7632,b__7634);
}
} else
{var c__7636 = cljs.core._first.call(null,args__7635);
var args__7637 = cljs.core._rest.call(null,args__7635);
if((argc === 3))
{if(f.cljs$lang$arity$3)
{return f.cljs$lang$arity$3(a__7632,b__7634,c__7636);
} else
{return f.call(null,a__7632,b__7634,c__7636);
}
} else
{var d__7638 = cljs.core._first.call(null,args__7637);
var args__7639 = cljs.core._rest.call(null,args__7637);
if((argc === 4))
{if(f.cljs$lang$arity$4)
{return f.cljs$lang$arity$4(a__7632,b__7634,c__7636,d__7638);
} else
{return f.call(null,a__7632,b__7634,c__7636,d__7638);
}
} else
{var e__7640 = cljs.core._first.call(null,args__7639);
var args__7641 = cljs.core._rest.call(null,args__7639);
if((argc === 5))
{if(f.cljs$lang$arity$5)
{return f.cljs$lang$arity$5(a__7632,b__7634,c__7636,d__7638,e__7640);
} else
{return f.call(null,a__7632,b__7634,c__7636,d__7638,e__7640);
}
} else
{var f__7642 = cljs.core._first.call(null,args__7641);
var args__7643 = cljs.core._rest.call(null,args__7641);
if((argc === 6))
{if(f__7642.cljs$lang$arity$6)
{return f__7642.cljs$lang$arity$6(a__7632,b__7634,c__7636,d__7638,e__7640,f__7642);
} else
{return f__7642.call(null,a__7632,b__7634,c__7636,d__7638,e__7640,f__7642);
}
} else
{var g__7644 = cljs.core._first.call(null,args__7643);
var args__7645 = cljs.core._rest.call(null,args__7643);
if((argc === 7))
{if(f__7642.cljs$lang$arity$7)
{return f__7642.cljs$lang$arity$7(a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644);
} else
{return f__7642.call(null,a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644);
}
} else
{var h__7646 = cljs.core._first.call(null,args__7645);
var args__7647 = cljs.core._rest.call(null,args__7645);
if((argc === 8))
{if(f__7642.cljs$lang$arity$8)
{return f__7642.cljs$lang$arity$8(a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646);
} else
{return f__7642.call(null,a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646);
}
} else
{var i__7648 = cljs.core._first.call(null,args__7647);
var args__7649 = cljs.core._rest.call(null,args__7647);
if((argc === 9))
{if(f__7642.cljs$lang$arity$9)
{return f__7642.cljs$lang$arity$9(a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646,i__7648);
} else
{return f__7642.call(null,a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646,i__7648);
}
} else
{var j__7650 = cljs.core._first.call(null,args__7649);
var args__7651 = cljs.core._rest.call(null,args__7649);
if((argc === 10))
{if(f__7642.cljs$lang$arity$10)
{return f__7642.cljs$lang$arity$10(a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646,i__7648,j__7650);
} else
{return f__7642.call(null,a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646,i__7648,j__7650);
}
} else
{var k__7652 = cljs.core._first.call(null,args__7651);
var args__7653 = cljs.core._rest.call(null,args__7651);
if((argc === 11))
{if(f__7642.cljs$lang$arity$11)
{return f__7642.cljs$lang$arity$11(a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646,i__7648,j__7650,k__7652);
} else
{return f__7642.call(null,a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646,i__7648,j__7650,k__7652);
}
} else
{var l__7654 = cljs.core._first.call(null,args__7653);
var args__7655 = cljs.core._rest.call(null,args__7653);
if((argc === 12))
{if(f__7642.cljs$lang$arity$12)
{return f__7642.cljs$lang$arity$12(a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646,i__7648,j__7650,k__7652,l__7654);
} else
{return f__7642.call(null,a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646,i__7648,j__7650,k__7652,l__7654);
}
} else
{var m__7656 = cljs.core._first.call(null,args__7655);
var args__7657 = cljs.core._rest.call(null,args__7655);
if((argc === 13))
{if(f__7642.cljs$lang$arity$13)
{return f__7642.cljs$lang$arity$13(a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646,i__7648,j__7650,k__7652,l__7654,m__7656);
} else
{return f__7642.call(null,a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646,i__7648,j__7650,k__7652,l__7654,m__7656);
}
} else
{var n__7658 = cljs.core._first.call(null,args__7657);
var args__7659 = cljs.core._rest.call(null,args__7657);
if((argc === 14))
{if(f__7642.cljs$lang$arity$14)
{return f__7642.cljs$lang$arity$14(a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646,i__7648,j__7650,k__7652,l__7654,m__7656,n__7658);
} else
{return f__7642.call(null,a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646,i__7648,j__7650,k__7652,l__7654,m__7656,n__7658);
}
} else
{var o__7660 = cljs.core._first.call(null,args__7659);
var args__7661 = cljs.core._rest.call(null,args__7659);
if((argc === 15))
{if(f__7642.cljs$lang$arity$15)
{return f__7642.cljs$lang$arity$15(a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646,i__7648,j__7650,k__7652,l__7654,m__7656,n__7658,o__7660);
} else
{return f__7642.call(null,a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646,i__7648,j__7650,k__7652,l__7654,m__7656,n__7658,o__7660);
}
} else
{var p__7662 = cljs.core._first.call(null,args__7661);
var args__7663 = cljs.core._rest.call(null,args__7661);
if((argc === 16))
{if(f__7642.cljs$lang$arity$16)
{return f__7642.cljs$lang$arity$16(a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646,i__7648,j__7650,k__7652,l__7654,m__7656,n__7658,o__7660,p__7662);
} else
{return f__7642.call(null,a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646,i__7648,j__7650,k__7652,l__7654,m__7656,n__7658,o__7660,p__7662);
}
} else
{var q__7664 = cljs.core._first.call(null,args__7663);
var args__7665 = cljs.core._rest.call(null,args__7663);
if((argc === 17))
{if(f__7642.cljs$lang$arity$17)
{return f__7642.cljs$lang$arity$17(a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646,i__7648,j__7650,k__7652,l__7654,m__7656,n__7658,o__7660,p__7662,q__7664);
} else
{return f__7642.call(null,a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646,i__7648,j__7650,k__7652,l__7654,m__7656,n__7658,o__7660,p__7662,q__7664);
}
} else
{var r__7666 = cljs.core._first.call(null,args__7665);
var args__7667 = cljs.core._rest.call(null,args__7665);
if((argc === 18))
{if(f__7642.cljs$lang$arity$18)
{return f__7642.cljs$lang$arity$18(a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646,i__7648,j__7650,k__7652,l__7654,m__7656,n__7658,o__7660,p__7662,q__7664,r__7666);
} else
{return f__7642.call(null,a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646,i__7648,j__7650,k__7652,l__7654,m__7656,n__7658,o__7660,p__7662,q__7664,r__7666);
}
} else
{var s__7668 = cljs.core._first.call(null,args__7667);
var args__7669 = cljs.core._rest.call(null,args__7667);
if((argc === 19))
{if(f__7642.cljs$lang$arity$19)
{return f__7642.cljs$lang$arity$19(a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646,i__7648,j__7650,k__7652,l__7654,m__7656,n__7658,o__7660,p__7662,q__7664,r__7666,s__7668);
} else
{return f__7642.call(null,a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646,i__7648,j__7650,k__7652,l__7654,m__7656,n__7658,o__7660,p__7662,q__7664,r__7666,s__7668);
}
} else
{var t__7670 = cljs.core._first.call(null,args__7669);
var args__7671 = cljs.core._rest.call(null,args__7669);
if((argc === 20))
{if(f__7642.cljs$lang$arity$20)
{return f__7642.cljs$lang$arity$20(a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646,i__7648,j__7650,k__7652,l__7654,m__7656,n__7658,o__7660,p__7662,q__7664,r__7666,s__7668,t__7670);
} else
{return f__7642.call(null,a__7632,b__7634,c__7636,d__7638,e__7640,f__7642,g__7644,h__7646,i__7648,j__7650,k__7652,l__7654,m__7656,n__7658,o__7660,p__7662,q__7664,r__7666,s__7668,t__7670);
}
} else
{throw (new Error("Only up to 20 arguments supported on functions"));
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
});
/**
* Applies fn f to the argument list formed by prepending intervening arguments to args.
* First cut.  Not lazy.  Needs to use emitted toApply.
* @param {...*} var_args
*/
cljs.core.apply = (function() {
var apply = null;
var apply__2 = (function (f,args){
var fixed_arity__7686 = f.cljs$lang$maxFixedArity;
if(cljs.core.truth_(f.cljs$lang$applyTo))
{var bc__7687 = cljs.core.bounded_count.call(null,args,(fixed_arity__7686 + 1));
if((bc__7687 <= fixed_arity__7686))
{return cljs.core.apply_to.call(null,f,bc__7687,args);
} else
{return f.cljs$lang$applyTo(args);
}
} else
{return f.apply(f,cljs.core.to_array.call(null,args));
}
});
var apply__3 = (function (f,x,args){
var arglist__7688 = cljs.core.list_STAR_.call(null,x,args);
var fixed_arity__7689 = f.cljs$lang$maxFixedArity;
if(cljs.core.truth_(f.cljs$lang$applyTo))
{var bc__7690 = cljs.core.bounded_count.call(null,arglist__7688,(fixed_arity__7689 + 1));
if((bc__7690 <= fixed_arity__7689))
{return cljs.core.apply_to.call(null,f,bc__7690,arglist__7688);
} else
{return f.cljs$lang$applyTo(arglist__7688);
}
} else
{return f.apply(f,cljs.core.to_array.call(null,arglist__7688));
}
});
var apply__4 = (function (f,x,y,args){
var arglist__7691 = cljs.core.list_STAR_.call(null,x,y,args);
var fixed_arity__7692 = f.cljs$lang$maxFixedArity;
if(cljs.core.truth_(f.cljs$lang$applyTo))
{var bc__7693 = cljs.core.bounded_count.call(null,arglist__7691,(fixed_arity__7692 + 1));
if((bc__7693 <= fixed_arity__7692))
{return cljs.core.apply_to.call(null,f,bc__7693,arglist__7691);
} else
{return f.cljs$lang$applyTo(arglist__7691);
}
} else
{return f.apply(f,cljs.core.to_array.call(null,arglist__7691));
}
});
var apply__5 = (function (f,x,y,z,args){
var arglist__7694 = cljs.core.list_STAR_.call(null,x,y,z,args);
var fixed_arity__7695 = f.cljs$lang$maxFixedArity;
if(cljs.core.truth_(f.cljs$lang$applyTo))
{var bc__7696 = cljs.core.bounded_count.call(null,arglist__7694,(fixed_arity__7695 + 1));
if((bc__7696 <= fixed_arity__7695))
{return cljs.core.apply_to.call(null,f,bc__7696,arglist__7694);
} else
{return f.cljs$lang$applyTo(arglist__7694);
}
} else
{return f.apply(f,cljs.core.to_array.call(null,arglist__7694));
}
});
var apply__6 = (function() { 
var G__7700__delegate = function (f,a,b,c,d,args){
var arglist__7697 = cljs.core.cons.call(null,a,cljs.core.cons.call(null,b,cljs.core.cons.call(null,c,cljs.core.cons.call(null,d,cljs.core.spread.call(null,args)))));
var fixed_arity__7698 = f.cljs$lang$maxFixedArity;
if(cljs.core.truth_(f.cljs$lang$applyTo))
{var bc__7699 = cljs.core.bounded_count.call(null,arglist__7697,(fixed_arity__7698 + 1));
if((bc__7699 <= fixed_arity__7698))
{return cljs.core.apply_to.call(null,f,bc__7699,arglist__7697);
} else
{return f.cljs$lang$applyTo(arglist__7697);
}
} else
{return f.apply(f,cljs.core.to_array.call(null,arglist__7697));
}
};
var G__7700 = function (f,a,b,c,d,var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 5),0);
} 
return G__7700__delegate.call(this, f, a, b, c, d, args);
};
G__7700.cljs$lang$maxFixedArity = 5;
G__7700.cljs$lang$applyTo = (function (arglist__7701){
var f = cljs.core.first(arglist__7701);
var a = cljs.core.first(cljs.core.next(arglist__7701));
var b = cljs.core.first(cljs.core.next(cljs.core.next(arglist__7701)));
var c = cljs.core.first(cljs.core.next(cljs.core.next(cljs.core.next(arglist__7701))));
var d = cljs.core.first(cljs.core.next(cljs.core.next(cljs.core.next(cljs.core.next(arglist__7701)))));
var args = cljs.core.rest(cljs.core.next(cljs.core.next(cljs.core.next(cljs.core.next(arglist__7701)))));
return G__7700__delegate(f, a, b, c, d, args);
});
G__7700.cljs$lang$arity$variadic = G__7700__delegate;
return G__7700;
})()
;
apply = function(f,a,b,c,d,var_args){
var args = var_args;
switch(arguments.length){
case 2:
return apply__2.call(this,f,a);
case 3:
return apply__3.call(this,f,a,b);
case 4:
return apply__4.call(this,f,a,b,c);
case 5:
return apply__5.call(this,f,a,b,c,d);
default:
return apply__6.cljs$lang$arity$variadic(f,a,b,c,d, cljs.core.array_seq(arguments, 5));
}
throw('Invalid arity: ' + arguments.length);
};
apply.cljs$lang$maxFixedArity = 5;
apply.cljs$lang$applyTo = apply__6.cljs$lang$applyTo;
apply.cljs$lang$arity$2 = apply__2;
apply.cljs$lang$arity$3 = apply__3;
apply.cljs$lang$arity$4 = apply__4;
apply.cljs$lang$arity$5 = apply__5;
apply.cljs$lang$arity$variadic = apply__6.cljs$lang$arity$variadic;
return apply;
})()
;
/**
* Returns an object of the same type and value as obj, with
* (apply f (meta obj) args) as its metadata.
* @param {...*} var_args
*/
cljs.core.vary_meta = (function() { 
var vary_meta__delegate = function (obj,f,args){
return cljs.core.with_meta.call(null,obj,cljs.core.apply.call(null,f,cljs.core.meta.call(null,obj),args));
};
var vary_meta = function (obj,f,var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 2),0);
} 
return vary_meta__delegate.call(this, obj, f, args);
};
vary_meta.cljs$lang$maxFixedArity = 2;
vary_meta.cljs$lang$applyTo = (function (arglist__7702){
var obj = cljs.core.first(arglist__7702);
var f = cljs.core.first(cljs.core.next(arglist__7702));
var args = cljs.core.rest(cljs.core.next(arglist__7702));
return vary_meta__delegate(obj, f, args);
});
vary_meta.cljs$lang$arity$variadic = vary_meta__delegate;
return vary_meta;
})()
;
/**
* Same as (not (= obj1 obj2))
* @param {...*} var_args
*/
cljs.core.not_EQ_ = (function() {
var not_EQ_ = null;
var not_EQ___1 = (function (x){
return false;
});
var not_EQ___2 = (function (x,y){
return !(cljs.core._EQ_.call(null,x,y));
});
var not_EQ___3 = (function() { 
var G__7703__delegate = function (x,y,more){
return cljs.core.not.call(null,cljs.core.apply.call(null,cljs.core._EQ_,x,y,more));
};
var G__7703 = function (x,y,var_args){
var more = null;
if (goog.isDef(var_args)) {
  more = cljs.core.array_seq(Array.prototype.slice.call(arguments, 2),0);
} 
return G__7703__delegate.call(this, x, y, more);
};
G__7703.cljs$lang$maxFixedArity = 2;
G__7703.cljs$lang$applyTo = (function (arglist__7704){
var x = cljs.core.first(arglist__7704);
var y = cljs.core.first(cljs.core.next(arglist__7704));
var more = cljs.core.rest(cljs.core.next(arglist__7704));
return G__7703__delegate(x, y, more);
});
G__7703.cljs$lang$arity$variadic = G__7703__delegate;
return G__7703;
})()
;
not_EQ_ = function(x,y,var_args){
var more = var_args;
switch(arguments.length){
case 1:
return not_EQ___1.call(this,x);
case 2:
return not_EQ___2.call(this,x,y);
default:
return not_EQ___3.cljs$lang$arity$variadic(x,y, cljs.core.array_seq(arguments, 2));
}
throw('Invalid arity: ' + arguments.length);
};
not_EQ_.cljs$lang$maxFixedArity = 2;
not_EQ_.cljs$lang$applyTo = not_EQ___3.cljs$lang$applyTo;
not_EQ_.cljs$lang$arity$1 = not_EQ___1;
not_EQ_.cljs$lang$arity$2 = not_EQ___2;
not_EQ_.cljs$lang$arity$variadic = not_EQ___3.cljs$lang$arity$variadic;
return not_EQ_;
})()
;
/**
* If coll is empty, returns nil, else coll
*/
cljs.core.not_empty = (function not_empty(coll){
if(cljs.core.seq.call(null,coll))
{return coll;
} else
{return null;
}
});
/**
* Returns true if (pred x) is logical true for every x in coll, else
* false.
*/
cljs.core.every_QMARK_ = (function every_QMARK_(pred,coll){
while(true){
if((cljs.core.seq.call(null,coll) == null))
{return true;
} else
{if(cljs.core.truth_(pred.call(null,cljs.core.first.call(null,coll))))
{{
var G__7705 = pred;
var G__7706 = cljs.core.next.call(null,coll);
pred = G__7705;
coll = G__7706;
continue;
}
} else
{if("\uFDD0'else")
{return false;
} else
{return null;
}
}
}
break;
}
});
/**
* Returns false if (pred x) is logical true for every x in
* coll, else true.
*/
cljs.core.not_every_QMARK_ = (function not_every_QMARK_(pred,coll){
return !(cljs.core.every_QMARK_.call(null,pred,coll));
});
/**
* Returns the first logical true value of (pred x) for any x in coll,
* else nil.  One common idiom is to use a set as pred, for example
* this will return :fred if :fred is in the sequence, otherwise nil:
* (some #{:fred} coll)
*/
cljs.core.some = (function some(pred,coll){
while(true){
if(cljs.core.seq.call(null,coll))
{var or__3824__auto____7708 = pred.call(null,cljs.core.first.call(null,coll));
if(cljs.core.truth_(or__3824__auto____7708))
{return or__3824__auto____7708;
} else
{{
var G__7709 = pred;
var G__7710 = cljs.core.next.call(null,coll);
pred = G__7709;
coll = G__7710;
continue;
}
}
} else
{return null;
}
break;
}
});
/**
* Returns false if (pred x) is logical true for any x in coll,
* else true.
*/
cljs.core.not_any_QMARK_ = (function not_any_QMARK_(pred,coll){
return cljs.core.not.call(null,cljs.core.some.call(null,pred,coll));
});
/**
* Returns true if n is even, throws an exception if n is not an integer
*/
cljs.core.even_QMARK_ = (function even_QMARK_(n){
if(cljs.core.integer_QMARK_.call(null,n))
{return ((n & 1) === 0);
} else
{throw (new Error([cljs.core.str("Argument must be an integer: "),cljs.core.str(n)].join('')));
}
});
/**
* Returns true if n is odd, throws an exception if n is not an integer
*/
cljs.core.odd_QMARK_ = (function odd_QMARK_(n){
return !(cljs.core.even_QMARK_.call(null,n));
});
cljs.core.identity = (function identity(x){
return x;
});
/**
* Takes a fn f and returns a fn that takes the same arguments as f,
* has the same effects, if any, and returns the opposite truth value.
*/
cljs.core.complement = (function complement(f){
return (function() {
var G__7711 = null;
var G__7711__0 = (function (){
return cljs.core.not.call(null,f.call(null));
});
var G__7711__1 = (function (x){
return cljs.core.not.call(null,f.call(null,x));
});
var G__7711__2 = (function (x,y){
return cljs.core.not.call(null,f.call(null,x,y));
});
var G__7711__3 = (function() { 
var G__7712__delegate = function (x,y,zs){
return cljs.core.not.call(null,cljs.core.apply.call(null,f,x,y,zs));
};
var G__7712 = function (x,y,var_args){
var zs = null;
if (goog.isDef(var_args)) {
  zs = cljs.core.array_seq(Array.prototype.slice.call(arguments, 2),0);
} 
return G__7712__delegate.call(this, x, y, zs);
};
G__7712.cljs$lang$maxFixedArity = 2;
G__7712.cljs$lang$applyTo = (function (arglist__7713){
var x = cljs.core.first(arglist__7713);
var y = cljs.core.first(cljs.core.next(arglist__7713));
var zs = cljs.core.rest(cljs.core.next(arglist__7713));
return G__7712__delegate(x, y, zs);
});
G__7712.cljs$lang$arity$variadic = G__7712__delegate;
return G__7712;
})()
;
G__7711 = function(x,y,var_args){
var zs = var_args;
switch(arguments.length){
case 0:
return G__7711__0.call(this);
case 1:
return G__7711__1.call(this,x);
case 2:
return G__7711__2.call(this,x,y);
default:
return G__7711__3.cljs$lang$arity$variadic(x,y, cljs.core.array_seq(arguments, 2));
}
throw('Invalid arity: ' + arguments.length);
};
G__7711.cljs$lang$maxFixedArity = 2;
G__7711.cljs$lang$applyTo = G__7711__3.cljs$lang$applyTo;
return G__7711;
})()
});
/**
* Returns a function that takes any number of arguments and returns x.
*/
cljs.core.constantly = (function constantly(x){
return (function() { 
var G__7714__delegate = function (args){
return x;
};
var G__7714 = function (var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 0),0);
} 
return G__7714__delegate.call(this, args);
};
G__7714.cljs$lang$maxFixedArity = 0;
G__7714.cljs$lang$applyTo = (function (arglist__7715){
var args = cljs.core.seq(arglist__7715);;
return G__7714__delegate(args);
});
G__7714.cljs$lang$arity$variadic = G__7714__delegate;
return G__7714;
})()
;
});
/**
* Takes a set of functions and returns a fn that is the composition
* of those fns.  The returned fn takes a variable number of args,
* applies the rightmost of fns to the args, the next
* fn (right-to-left) to the result, etc.
* @param {...*} var_args
*/
cljs.core.comp = (function() {
var comp = null;
var comp__0 = (function (){
return cljs.core.identity;
});
var comp__1 = (function (f){
return f;
});
var comp__2 = (function (f,g){
return (function() {
var G__7722 = null;
var G__7722__0 = (function (){
return f.call(null,g.call(null));
});
var G__7722__1 = (function (x){
return f.call(null,g.call(null,x));
});
var G__7722__2 = (function (x,y){
return f.call(null,g.call(null,x,y));
});
var G__7722__3 = (function (x,y,z){
return f.call(null,g.call(null,x,y,z));
});
var G__7722__4 = (function() { 
var G__7723__delegate = function (x,y,z,args){
return f.call(null,cljs.core.apply.call(null,g,x,y,z,args));
};
var G__7723 = function (x,y,z,var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return G__7723__delegate.call(this, x, y, z, args);
};
G__7723.cljs$lang$maxFixedArity = 3;
G__7723.cljs$lang$applyTo = (function (arglist__7724){
var x = cljs.core.first(arglist__7724);
var y = cljs.core.first(cljs.core.next(arglist__7724));
var z = cljs.core.first(cljs.core.next(cljs.core.next(arglist__7724)));
var args = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__7724)));
return G__7723__delegate(x, y, z, args);
});
G__7723.cljs$lang$arity$variadic = G__7723__delegate;
return G__7723;
})()
;
G__7722 = function(x,y,z,var_args){
var args = var_args;
switch(arguments.length){
case 0:
return G__7722__0.call(this);
case 1:
return G__7722__1.call(this,x);
case 2:
return G__7722__2.call(this,x,y);
case 3:
return G__7722__3.call(this,x,y,z);
default:
return G__7722__4.cljs$lang$arity$variadic(x,y,z, cljs.core.array_seq(arguments, 3));
}
throw('Invalid arity: ' + arguments.length);
};
G__7722.cljs$lang$maxFixedArity = 3;
G__7722.cljs$lang$applyTo = G__7722__4.cljs$lang$applyTo;
return G__7722;
})()
});
var comp__3 = (function (f,g,h){
return (function() {
var G__7725 = null;
var G__7725__0 = (function (){
return f.call(null,g.call(null,h.call(null)));
});
var G__7725__1 = (function (x){
return f.call(null,g.call(null,h.call(null,x)));
});
var G__7725__2 = (function (x,y){
return f.call(null,g.call(null,h.call(null,x,y)));
});
var G__7725__3 = (function (x,y,z){
return f.call(null,g.call(null,h.call(null,x,y,z)));
});
var G__7725__4 = (function() { 
var G__7726__delegate = function (x,y,z,args){
return f.call(null,g.call(null,cljs.core.apply.call(null,h,x,y,z,args)));
};
var G__7726 = function (x,y,z,var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return G__7726__delegate.call(this, x, y, z, args);
};
G__7726.cljs$lang$maxFixedArity = 3;
G__7726.cljs$lang$applyTo = (function (arglist__7727){
var x = cljs.core.first(arglist__7727);
var y = cljs.core.first(cljs.core.next(arglist__7727));
var z = cljs.core.first(cljs.core.next(cljs.core.next(arglist__7727)));
var args = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__7727)));
return G__7726__delegate(x, y, z, args);
});
G__7726.cljs$lang$arity$variadic = G__7726__delegate;
return G__7726;
})()
;
G__7725 = function(x,y,z,var_args){
var args = var_args;
switch(arguments.length){
case 0:
return G__7725__0.call(this);
case 1:
return G__7725__1.call(this,x);
case 2:
return G__7725__2.call(this,x,y);
case 3:
return G__7725__3.call(this,x,y,z);
default:
return G__7725__4.cljs$lang$arity$variadic(x,y,z, cljs.core.array_seq(arguments, 3));
}
throw('Invalid arity: ' + arguments.length);
};
G__7725.cljs$lang$maxFixedArity = 3;
G__7725.cljs$lang$applyTo = G__7725__4.cljs$lang$applyTo;
return G__7725;
})()
});
var comp__4 = (function() { 
var G__7728__delegate = function (f1,f2,f3,fs){
var fs__7719 = cljs.core.reverse.call(null,cljs.core.list_STAR_.call(null,f1,f2,f3,fs));
return (function() { 
var G__7729__delegate = function (args){
var ret__7720 = cljs.core.apply.call(null,cljs.core.first.call(null,fs__7719),args);
var fs__7721 = cljs.core.next.call(null,fs__7719);
while(true){
if(fs__7721)
{{
var G__7730 = cljs.core.first.call(null,fs__7721).call(null,ret__7720);
var G__7731 = cljs.core.next.call(null,fs__7721);
ret__7720 = G__7730;
fs__7721 = G__7731;
continue;
}
} else
{return ret__7720;
}
break;
}
};
var G__7729 = function (var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 0),0);
} 
return G__7729__delegate.call(this, args);
};
G__7729.cljs$lang$maxFixedArity = 0;
G__7729.cljs$lang$applyTo = (function (arglist__7732){
var args = cljs.core.seq(arglist__7732);;
return G__7729__delegate(args);
});
G__7729.cljs$lang$arity$variadic = G__7729__delegate;
return G__7729;
})()
;
};
var G__7728 = function (f1,f2,f3,var_args){
var fs = null;
if (goog.isDef(var_args)) {
  fs = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return G__7728__delegate.call(this, f1, f2, f3, fs);
};
G__7728.cljs$lang$maxFixedArity = 3;
G__7728.cljs$lang$applyTo = (function (arglist__7733){
var f1 = cljs.core.first(arglist__7733);
var f2 = cljs.core.first(cljs.core.next(arglist__7733));
var f3 = cljs.core.first(cljs.core.next(cljs.core.next(arglist__7733)));
var fs = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__7733)));
return G__7728__delegate(f1, f2, f3, fs);
});
G__7728.cljs$lang$arity$variadic = G__7728__delegate;
return G__7728;
})()
;
comp = function(f1,f2,f3,var_args){
var fs = var_args;
switch(arguments.length){
case 0:
return comp__0.call(this);
case 1:
return comp__1.call(this,f1);
case 2:
return comp__2.call(this,f1,f2);
case 3:
return comp__3.call(this,f1,f2,f3);
default:
return comp__4.cljs$lang$arity$variadic(f1,f2,f3, cljs.core.array_seq(arguments, 3));
}
throw('Invalid arity: ' + arguments.length);
};
comp.cljs$lang$maxFixedArity = 3;
comp.cljs$lang$applyTo = comp__4.cljs$lang$applyTo;
comp.cljs$lang$arity$0 = comp__0;
comp.cljs$lang$arity$1 = comp__1;
comp.cljs$lang$arity$2 = comp__2;
comp.cljs$lang$arity$3 = comp__3;
comp.cljs$lang$arity$variadic = comp__4.cljs$lang$arity$variadic;
return comp;
})()
;
/**
* Takes a function f and fewer than the normal arguments to f, and
* returns a fn that takes a variable number of additional args. When
* called, the returned function calls f with args + additional args.
* @param {...*} var_args
*/
cljs.core.partial = (function() {
var partial = null;
var partial__2 = (function (f,arg1){
return (function() { 
var G__7734__delegate = function (args){
return cljs.core.apply.call(null,f,arg1,args);
};
var G__7734 = function (var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 0),0);
} 
return G__7734__delegate.call(this, args);
};
G__7734.cljs$lang$maxFixedArity = 0;
G__7734.cljs$lang$applyTo = (function (arglist__7735){
var args = cljs.core.seq(arglist__7735);;
return G__7734__delegate(args);
});
G__7734.cljs$lang$arity$variadic = G__7734__delegate;
return G__7734;
})()
;
});
var partial__3 = (function (f,arg1,arg2){
return (function() { 
var G__7736__delegate = function (args){
return cljs.core.apply.call(null,f,arg1,arg2,args);
};
var G__7736 = function (var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 0),0);
} 
return G__7736__delegate.call(this, args);
};
G__7736.cljs$lang$maxFixedArity = 0;
G__7736.cljs$lang$applyTo = (function (arglist__7737){
var args = cljs.core.seq(arglist__7737);;
return G__7736__delegate(args);
});
G__7736.cljs$lang$arity$variadic = G__7736__delegate;
return G__7736;
})()
;
});
var partial__4 = (function (f,arg1,arg2,arg3){
return (function() { 
var G__7738__delegate = function (args){
return cljs.core.apply.call(null,f,arg1,arg2,arg3,args);
};
var G__7738 = function (var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 0),0);
} 
return G__7738__delegate.call(this, args);
};
G__7738.cljs$lang$maxFixedArity = 0;
G__7738.cljs$lang$applyTo = (function (arglist__7739){
var args = cljs.core.seq(arglist__7739);;
return G__7738__delegate(args);
});
G__7738.cljs$lang$arity$variadic = G__7738__delegate;
return G__7738;
})()
;
});
var partial__5 = (function() { 
var G__7740__delegate = function (f,arg1,arg2,arg3,more){
return (function() { 
var G__7741__delegate = function (args){
return cljs.core.apply.call(null,f,arg1,arg2,arg3,cljs.core.concat.call(null,more,args));
};
var G__7741 = function (var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 0),0);
} 
return G__7741__delegate.call(this, args);
};
G__7741.cljs$lang$maxFixedArity = 0;
G__7741.cljs$lang$applyTo = (function (arglist__7742){
var args = cljs.core.seq(arglist__7742);;
return G__7741__delegate(args);
});
G__7741.cljs$lang$arity$variadic = G__7741__delegate;
return G__7741;
})()
;
};
var G__7740 = function (f,arg1,arg2,arg3,var_args){
var more = null;
if (goog.isDef(var_args)) {
  more = cljs.core.array_seq(Array.prototype.slice.call(arguments, 4),0);
} 
return G__7740__delegate.call(this, f, arg1, arg2, arg3, more);
};
G__7740.cljs$lang$maxFixedArity = 4;
G__7740.cljs$lang$applyTo = (function (arglist__7743){
var f = cljs.core.first(arglist__7743);
var arg1 = cljs.core.first(cljs.core.next(arglist__7743));
var arg2 = cljs.core.first(cljs.core.next(cljs.core.next(arglist__7743)));
var arg3 = cljs.core.first(cljs.core.next(cljs.core.next(cljs.core.next(arglist__7743))));
var more = cljs.core.rest(cljs.core.next(cljs.core.next(cljs.core.next(arglist__7743))));
return G__7740__delegate(f, arg1, arg2, arg3, more);
});
G__7740.cljs$lang$arity$variadic = G__7740__delegate;
return G__7740;
})()
;
partial = function(f,arg1,arg2,arg3,var_args){
var more = var_args;
switch(arguments.length){
case 2:
return partial__2.call(this,f,arg1);
case 3:
return partial__3.call(this,f,arg1,arg2);
case 4:
return partial__4.call(this,f,arg1,arg2,arg3);
default:
return partial__5.cljs$lang$arity$variadic(f,arg1,arg2,arg3, cljs.core.array_seq(arguments, 4));
}
throw('Invalid arity: ' + arguments.length);
};
partial.cljs$lang$maxFixedArity = 4;
partial.cljs$lang$applyTo = partial__5.cljs$lang$applyTo;
partial.cljs$lang$arity$2 = partial__2;
partial.cljs$lang$arity$3 = partial__3;
partial.cljs$lang$arity$4 = partial__4;
partial.cljs$lang$arity$variadic = partial__5.cljs$lang$arity$variadic;
return partial;
})()
;
/**
* Takes a function f, and returns a function that calls f, replacing
* a nil first argument to f with the supplied value x. Higher arity
* versions can replace arguments in the second and third
* positions (y, z). Note that the function f can take any number of
* arguments, not just the one(s) being nil-patched.
*/
cljs.core.fnil = (function() {
var fnil = null;
var fnil__2 = (function (f,x){
return (function() {
var G__7744 = null;
var G__7744__1 = (function (a){
return f.call(null,(((a == null))?x:a));
});
var G__7744__2 = (function (a,b){
return f.call(null,(((a == null))?x:a),b);
});
var G__7744__3 = (function (a,b,c){
return f.call(null,(((a == null))?x:a),b,c);
});
var G__7744__4 = (function() { 
var G__7745__delegate = function (a,b,c,ds){
return cljs.core.apply.call(null,f,(((a == null))?x:a),b,c,ds);
};
var G__7745 = function (a,b,c,var_args){
var ds = null;
if (goog.isDef(var_args)) {
  ds = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return G__7745__delegate.call(this, a, b, c, ds);
};
G__7745.cljs$lang$maxFixedArity = 3;
G__7745.cljs$lang$applyTo = (function (arglist__7746){
var a = cljs.core.first(arglist__7746);
var b = cljs.core.first(cljs.core.next(arglist__7746));
var c = cljs.core.first(cljs.core.next(cljs.core.next(arglist__7746)));
var ds = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__7746)));
return G__7745__delegate(a, b, c, ds);
});
G__7745.cljs$lang$arity$variadic = G__7745__delegate;
return G__7745;
})()
;
G__7744 = function(a,b,c,var_args){
var ds = var_args;
switch(arguments.length){
case 1:
return G__7744__1.call(this,a);
case 2:
return G__7744__2.call(this,a,b);
case 3:
return G__7744__3.call(this,a,b,c);
default:
return G__7744__4.cljs$lang$arity$variadic(a,b,c, cljs.core.array_seq(arguments, 3));
}
throw('Invalid arity: ' + arguments.length);
};
G__7744.cljs$lang$maxFixedArity = 3;
G__7744.cljs$lang$applyTo = G__7744__4.cljs$lang$applyTo;
return G__7744;
})()
});
var fnil__3 = (function (f,x,y){
return (function() {
var G__7747 = null;
var G__7747__2 = (function (a,b){
return f.call(null,(((a == null))?x:a),(((b == null))?y:b));
});
var G__7747__3 = (function (a,b,c){
return f.call(null,(((a == null))?x:a),(((b == null))?y:b),c);
});
var G__7747__4 = (function() { 
var G__7748__delegate = function (a,b,c,ds){
return cljs.core.apply.call(null,f,(((a == null))?x:a),(((b == null))?y:b),c,ds);
};
var G__7748 = function (a,b,c,var_args){
var ds = null;
if (goog.isDef(var_args)) {
  ds = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return G__7748__delegate.call(this, a, b, c, ds);
};
G__7748.cljs$lang$maxFixedArity = 3;
G__7748.cljs$lang$applyTo = (function (arglist__7749){
var a = cljs.core.first(arglist__7749);
var b = cljs.core.first(cljs.core.next(arglist__7749));
var c = cljs.core.first(cljs.core.next(cljs.core.next(arglist__7749)));
var ds = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__7749)));
return G__7748__delegate(a, b, c, ds);
});
G__7748.cljs$lang$arity$variadic = G__7748__delegate;
return G__7748;
})()
;
G__7747 = function(a,b,c,var_args){
var ds = var_args;
switch(arguments.length){
case 2:
return G__7747__2.call(this,a,b);
case 3:
return G__7747__3.call(this,a,b,c);
default:
return G__7747__4.cljs$lang$arity$variadic(a,b,c, cljs.core.array_seq(arguments, 3));
}
throw('Invalid arity: ' + arguments.length);
};
G__7747.cljs$lang$maxFixedArity = 3;
G__7747.cljs$lang$applyTo = G__7747__4.cljs$lang$applyTo;
return G__7747;
})()
});
var fnil__4 = (function (f,x,y,z){
return (function() {
var G__7750 = null;
var G__7750__2 = (function (a,b){
return f.call(null,(((a == null))?x:a),(((b == null))?y:b));
});
var G__7750__3 = (function (a,b,c){
return f.call(null,(((a == null))?x:a),(((b == null))?y:b),(((c == null))?z:c));
});
var G__7750__4 = (function() { 
var G__7751__delegate = function (a,b,c,ds){
return cljs.core.apply.call(null,f,(((a == null))?x:a),(((b == null))?y:b),(((c == null))?z:c),ds);
};
var G__7751 = function (a,b,c,var_args){
var ds = null;
if (goog.isDef(var_args)) {
  ds = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return G__7751__delegate.call(this, a, b, c, ds);
};
G__7751.cljs$lang$maxFixedArity = 3;
G__7751.cljs$lang$applyTo = (function (arglist__7752){
var a = cljs.core.first(arglist__7752);
var b = cljs.core.first(cljs.core.next(arglist__7752));
var c = cljs.core.first(cljs.core.next(cljs.core.next(arglist__7752)));
var ds = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__7752)));
return G__7751__delegate(a, b, c, ds);
});
G__7751.cljs$lang$arity$variadic = G__7751__delegate;
return G__7751;
})()
;
G__7750 = function(a,b,c,var_args){
var ds = var_args;
switch(arguments.length){
case 2:
return G__7750__2.call(this,a,b);
case 3:
return G__7750__3.call(this,a,b,c);
default:
return G__7750__4.cljs$lang$arity$variadic(a,b,c, cljs.core.array_seq(arguments, 3));
}
throw('Invalid arity: ' + arguments.length);
};
G__7750.cljs$lang$maxFixedArity = 3;
G__7750.cljs$lang$applyTo = G__7750__4.cljs$lang$applyTo;
return G__7750;
})()
});
fnil = function(f,x,y,z){
switch(arguments.length){
case 2:
return fnil__2.call(this,f,x);
case 3:
return fnil__3.call(this,f,x,y);
case 4:
return fnil__4.call(this,f,x,y,z);
}
throw('Invalid arity: ' + arguments.length);
};
fnil.cljs$lang$arity$2 = fnil__2;
fnil.cljs$lang$arity$3 = fnil__3;
fnil.cljs$lang$arity$4 = fnil__4;
return fnil;
})()
;
/**
* Returns a lazy sequence consisting of the result of applying f to 0
* and the first item of coll, followed by applying f to 1 and the second
* item in coll, etc, until coll is exhausted. Thus function f should
* accept 2 arguments, index and item.
*/
cljs.core.map_indexed = (function map_indexed(f,coll){
var mapi__7768 = (function mapi(idx,coll){
return (new cljs.core.LazySeq(null,false,(function (){
var temp__3974__auto____7776 = cljs.core.seq.call(null,coll);
if(temp__3974__auto____7776)
{var s__7777 = temp__3974__auto____7776;
if(cljs.core.chunked_seq_QMARK_.call(null,s__7777))
{var c__7778 = cljs.core.chunk_first.call(null,s__7777);
var size__7779 = cljs.core.count.call(null,c__7778);
var b__7780 = cljs.core.chunk_buffer.call(null,size__7779);
var n__2555__auto____7781 = size__7779;
var i__7782 = 0;
while(true){
if((i__7782 < n__2555__auto____7781))
{cljs.core.chunk_append.call(null,b__7780,f.call(null,(idx + i__7782),cljs.core._nth.call(null,c__7778,i__7782)));
{
var G__7783 = (i__7782 + 1);
i__7782 = G__7783;
continue;
}
} else
{}
break;
}
return cljs.core.chunk_cons.call(null,cljs.core.chunk.call(null,b__7780),mapi.call(null,(idx + size__7779),cljs.core.chunk_rest.call(null,s__7777)));
} else
{return cljs.core.cons.call(null,f.call(null,idx,cljs.core.first.call(null,s__7777)),mapi.call(null,(idx + 1),cljs.core.rest.call(null,s__7777)));
}
} else
{return null;
}
}),null));
});
return mapi__7768.call(null,0,coll);
});
/**
* Returns a lazy sequence of the non-nil results of (f item). Note,
* this means false return values will be included.  f must be free of
* side-effects.
*/
cljs.core.keep = (function keep(f,coll){
return (new cljs.core.LazySeq(null,false,(function (){
var temp__3974__auto____7793 = cljs.core.seq.call(null,coll);
if(temp__3974__auto____7793)
{var s__7794 = temp__3974__auto____7793;
if(cljs.core.chunked_seq_QMARK_.call(null,s__7794))
{var c__7795 = cljs.core.chunk_first.call(null,s__7794);
var size__7796 = cljs.core.count.call(null,c__7795);
var b__7797 = cljs.core.chunk_buffer.call(null,size__7796);
var n__2555__auto____7798 = size__7796;
var i__7799 = 0;
while(true){
if((i__7799 < n__2555__auto____7798))
{var x__7800 = f.call(null,cljs.core._nth.call(null,c__7795,i__7799));
if((x__7800 == null))
{} else
{cljs.core.chunk_append.call(null,b__7797,x__7800);
}
{
var G__7802 = (i__7799 + 1);
i__7799 = G__7802;
continue;
}
} else
{}
break;
}
return cljs.core.chunk_cons.call(null,cljs.core.chunk.call(null,b__7797),keep.call(null,f,cljs.core.chunk_rest.call(null,s__7794)));
} else
{var x__7801 = f.call(null,cljs.core.first.call(null,s__7794));
if((x__7801 == null))
{return keep.call(null,f,cljs.core.rest.call(null,s__7794));
} else
{return cljs.core.cons.call(null,x__7801,keep.call(null,f,cljs.core.rest.call(null,s__7794)));
}
}
} else
{return null;
}
}),null));
});
/**
* Returns a lazy sequence of the non-nil results of (f index item). Note,
* this means false return values will be included.  f must be free of
* side-effects.
*/
cljs.core.keep_indexed = (function keep_indexed(f,coll){
var keepi__7828 = (function keepi(idx,coll){
return (new cljs.core.LazySeq(null,false,(function (){
var temp__3974__auto____7838 = cljs.core.seq.call(null,coll);
if(temp__3974__auto____7838)
{var s__7839 = temp__3974__auto____7838;
if(cljs.core.chunked_seq_QMARK_.call(null,s__7839))
{var c__7840 = cljs.core.chunk_first.call(null,s__7839);
var size__7841 = cljs.core.count.call(null,c__7840);
var b__7842 = cljs.core.chunk_buffer.call(null,size__7841);
var n__2555__auto____7843 = size__7841;
var i__7844 = 0;
while(true){
if((i__7844 < n__2555__auto____7843))
{var x__7845 = f.call(null,(idx + i__7844),cljs.core._nth.call(null,c__7840,i__7844));
if((x__7845 == null))
{} else
{cljs.core.chunk_append.call(null,b__7842,x__7845);
}
{
var G__7847 = (i__7844 + 1);
i__7844 = G__7847;
continue;
}
} else
{}
break;
}
return cljs.core.chunk_cons.call(null,cljs.core.chunk.call(null,b__7842),keepi.call(null,(idx + size__7841),cljs.core.chunk_rest.call(null,s__7839)));
} else
{var x__7846 = f.call(null,idx,cljs.core.first.call(null,s__7839));
if((x__7846 == null))
{return keepi.call(null,(idx + 1),cljs.core.rest.call(null,s__7839));
} else
{return cljs.core.cons.call(null,x__7846,keepi.call(null,(idx + 1),cljs.core.rest.call(null,s__7839)));
}
}
} else
{return null;
}
}),null));
});
return keepi__7828.call(null,0,coll);
});
/**
* Takes a set of predicates and returns a function f that returns true if all of its
* composing predicates return a logical true value against all of its arguments, else it returns
* false. Note that f is short-circuiting in that it will stop execution on the first
* argument that triggers a logical false result against the original predicates.
* @param {...*} var_args
*/
cljs.core.every_pred = (function() {
var every_pred = null;
var every_pred__1 = (function (p){
return (function() {
var ep1 = null;
var ep1__0 = (function (){
return true;
});
var ep1__1 = (function (x){
return cljs.core.boolean$.call(null,p.call(null,x));
});
var ep1__2 = (function (x,y){
return cljs.core.boolean$.call(null,(function (){var and__3822__auto____7933 = p.call(null,x);
if(cljs.core.truth_(and__3822__auto____7933))
{return p.call(null,y);
} else
{return and__3822__auto____7933;
}
})());
});
var ep1__3 = (function (x,y,z){
return cljs.core.boolean$.call(null,(function (){var and__3822__auto____7934 = p.call(null,x);
if(cljs.core.truth_(and__3822__auto____7934))
{var and__3822__auto____7935 = p.call(null,y);
if(cljs.core.truth_(and__3822__auto____7935))
{return p.call(null,z);
} else
{return and__3822__auto____7935;
}
} else
{return and__3822__auto____7934;
}
})());
});
var ep1__4 = (function() { 
var G__8004__delegate = function (x,y,z,args){
return cljs.core.boolean$.call(null,(function (){var and__3822__auto____7936 = ep1.call(null,x,y,z);
if(cljs.core.truth_(and__3822__auto____7936))
{return cljs.core.every_QMARK_.call(null,p,args);
} else
{return and__3822__auto____7936;
}
})());
};
var G__8004 = function (x,y,z,var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return G__8004__delegate.call(this, x, y, z, args);
};
G__8004.cljs$lang$maxFixedArity = 3;
G__8004.cljs$lang$applyTo = (function (arglist__8005){
var x = cljs.core.first(arglist__8005);
var y = cljs.core.first(cljs.core.next(arglist__8005));
var z = cljs.core.first(cljs.core.next(cljs.core.next(arglist__8005)));
var args = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__8005)));
return G__8004__delegate(x, y, z, args);
});
G__8004.cljs$lang$arity$variadic = G__8004__delegate;
return G__8004;
})()
;
ep1 = function(x,y,z,var_args){
var args = var_args;
switch(arguments.length){
case 0:
return ep1__0.call(this);
case 1:
return ep1__1.call(this,x);
case 2:
return ep1__2.call(this,x,y);
case 3:
return ep1__3.call(this,x,y,z);
default:
return ep1__4.cljs$lang$arity$variadic(x,y,z, cljs.core.array_seq(arguments, 3));
}
throw('Invalid arity: ' + arguments.length);
};
ep1.cljs$lang$maxFixedArity = 3;
ep1.cljs$lang$applyTo = ep1__4.cljs$lang$applyTo;
ep1.cljs$lang$arity$0 = ep1__0;
ep1.cljs$lang$arity$1 = ep1__1;
ep1.cljs$lang$arity$2 = ep1__2;
ep1.cljs$lang$arity$3 = ep1__3;
ep1.cljs$lang$arity$variadic = ep1__4.cljs$lang$arity$variadic;
return ep1;
})()
});
var every_pred__2 = (function (p1,p2){
return (function() {
var ep2 = null;
var ep2__0 = (function (){
return true;
});
var ep2__1 = (function (x){
return cljs.core.boolean$.call(null,(function (){var and__3822__auto____7948 = p1.call(null,x);
if(cljs.core.truth_(and__3822__auto____7948))
{return p2.call(null,x);
} else
{return and__3822__auto____7948;
}
})());
});
var ep2__2 = (function (x,y){
return cljs.core.boolean$.call(null,(function (){var and__3822__auto____7949 = p1.call(null,x);
if(cljs.core.truth_(and__3822__auto____7949))
{var and__3822__auto____7950 = p1.call(null,y);
if(cljs.core.truth_(and__3822__auto____7950))
{var and__3822__auto____7951 = p2.call(null,x);
if(cljs.core.truth_(and__3822__auto____7951))
{return p2.call(null,y);
} else
{return and__3822__auto____7951;
}
} else
{return and__3822__auto____7950;
}
} else
{return and__3822__auto____7949;
}
})());
});
var ep2__3 = (function (x,y,z){
return cljs.core.boolean$.call(null,(function (){var and__3822__auto____7952 = p1.call(null,x);
if(cljs.core.truth_(and__3822__auto____7952))
{var and__3822__auto____7953 = p1.call(null,y);
if(cljs.core.truth_(and__3822__auto____7953))
{var and__3822__auto____7954 = p1.call(null,z);
if(cljs.core.truth_(and__3822__auto____7954))
{var and__3822__auto____7955 = p2.call(null,x);
if(cljs.core.truth_(and__3822__auto____7955))
{var and__3822__auto____7956 = p2.call(null,y);
if(cljs.core.truth_(and__3822__auto____7956))
{return p2.call(null,z);
} else
{return and__3822__auto____7956;
}
} else
{return and__3822__auto____7955;
}
} else
{return and__3822__auto____7954;
}
} else
{return and__3822__auto____7953;
}
} else
{return and__3822__auto____7952;
}
})());
});
var ep2__4 = (function() { 
var G__8006__delegate = function (x,y,z,args){
return cljs.core.boolean$.call(null,(function (){var and__3822__auto____7957 = ep2.call(null,x,y,z);
if(cljs.core.truth_(and__3822__auto____7957))
{return cljs.core.every_QMARK_.call(null,(function (p1__7803_SHARP_){
var and__3822__auto____7958 = p1.call(null,p1__7803_SHARP_);
if(cljs.core.truth_(and__3822__auto____7958))
{return p2.call(null,p1__7803_SHARP_);
} else
{return and__3822__auto____7958;
}
}),args);
} else
{return and__3822__auto____7957;
}
})());
};
var G__8006 = function (x,y,z,var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return G__8006__delegate.call(this, x, y, z, args);
};
G__8006.cljs$lang$maxFixedArity = 3;
G__8006.cljs$lang$applyTo = (function (arglist__8007){
var x = cljs.core.first(arglist__8007);
var y = cljs.core.first(cljs.core.next(arglist__8007));
var z = cljs.core.first(cljs.core.next(cljs.core.next(arglist__8007)));
var args = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__8007)));
return G__8006__delegate(x, y, z, args);
});
G__8006.cljs$lang$arity$variadic = G__8006__delegate;
return G__8006;
})()
;
ep2 = function(x,y,z,var_args){
var args = var_args;
switch(arguments.length){
case 0:
return ep2__0.call(this);
case 1:
return ep2__1.call(this,x);
case 2:
return ep2__2.call(this,x,y);
case 3:
return ep2__3.call(this,x,y,z);
default:
return ep2__4.cljs$lang$arity$variadic(x,y,z, cljs.core.array_seq(arguments, 3));
}
throw('Invalid arity: ' + arguments.length);
};
ep2.cljs$lang$maxFixedArity = 3;
ep2.cljs$lang$applyTo = ep2__4.cljs$lang$applyTo;
ep2.cljs$lang$arity$0 = ep2__0;
ep2.cljs$lang$arity$1 = ep2__1;
ep2.cljs$lang$arity$2 = ep2__2;
ep2.cljs$lang$arity$3 = ep2__3;
ep2.cljs$lang$arity$variadic = ep2__4.cljs$lang$arity$variadic;
return ep2;
})()
});
var every_pred__3 = (function (p1,p2,p3){
return (function() {
var ep3 = null;
var ep3__0 = (function (){
return true;
});
var ep3__1 = (function (x){
return cljs.core.boolean$.call(null,(function (){var and__3822__auto____7977 = p1.call(null,x);
if(cljs.core.truth_(and__3822__auto____7977))
{var and__3822__auto____7978 = p2.call(null,x);
if(cljs.core.truth_(and__3822__auto____7978))
{return p3.call(null,x);
} else
{return and__3822__auto____7978;
}
} else
{return and__3822__auto____7977;
}
})());
});
var ep3__2 = (function (x,y){
return cljs.core.boolean$.call(null,(function (){var and__3822__auto____7979 = p1.call(null,x);
if(cljs.core.truth_(and__3822__auto____7979))
{var and__3822__auto____7980 = p2.call(null,x);
if(cljs.core.truth_(and__3822__auto____7980))
{var and__3822__auto____7981 = p3.call(null,x);
if(cljs.core.truth_(and__3822__auto____7981))
{var and__3822__auto____7982 = p1.call(null,y);
if(cljs.core.truth_(and__3822__auto____7982))
{var and__3822__auto____7983 = p2.call(null,y);
if(cljs.core.truth_(and__3822__auto____7983))
{return p3.call(null,y);
} else
{return and__3822__auto____7983;
}
} else
{return and__3822__auto____7982;
}
} else
{return and__3822__auto____7981;
}
} else
{return and__3822__auto____7980;
}
} else
{return and__3822__auto____7979;
}
})());
});
var ep3__3 = (function (x,y,z){
return cljs.core.boolean$.call(null,(function (){var and__3822__auto____7984 = p1.call(null,x);
if(cljs.core.truth_(and__3822__auto____7984))
{var and__3822__auto____7985 = p2.call(null,x);
if(cljs.core.truth_(and__3822__auto____7985))
{var and__3822__auto____7986 = p3.call(null,x);
if(cljs.core.truth_(and__3822__auto____7986))
{var and__3822__auto____7987 = p1.call(null,y);
if(cljs.core.truth_(and__3822__auto____7987))
{var and__3822__auto____7988 = p2.call(null,y);
if(cljs.core.truth_(and__3822__auto____7988))
{var and__3822__auto____7989 = p3.call(null,y);
if(cljs.core.truth_(and__3822__auto____7989))
{var and__3822__auto____7990 = p1.call(null,z);
if(cljs.core.truth_(and__3822__auto____7990))
{var and__3822__auto____7991 = p2.call(null,z);
if(cljs.core.truth_(and__3822__auto____7991))
{return p3.call(null,z);
} else
{return and__3822__auto____7991;
}
} else
{return and__3822__auto____7990;
}
} else
{return and__3822__auto____7989;
}
} else
{return and__3822__auto____7988;
}
} else
{return and__3822__auto____7987;
}
} else
{return and__3822__auto____7986;
}
} else
{return and__3822__auto____7985;
}
} else
{return and__3822__auto____7984;
}
})());
});
var ep3__4 = (function() { 
var G__8008__delegate = function (x,y,z,args){
return cljs.core.boolean$.call(null,(function (){var and__3822__auto____7992 = ep3.call(null,x,y,z);
if(cljs.core.truth_(and__3822__auto____7992))
{return cljs.core.every_QMARK_.call(null,(function (p1__7804_SHARP_){
var and__3822__auto____7993 = p1.call(null,p1__7804_SHARP_);
if(cljs.core.truth_(and__3822__auto____7993))
{var and__3822__auto____7994 = p2.call(null,p1__7804_SHARP_);
if(cljs.core.truth_(and__3822__auto____7994))
{return p3.call(null,p1__7804_SHARP_);
} else
{return and__3822__auto____7994;
}
} else
{return and__3822__auto____7993;
}
}),args);
} else
{return and__3822__auto____7992;
}
})());
};
var G__8008 = function (x,y,z,var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return G__8008__delegate.call(this, x, y, z, args);
};
G__8008.cljs$lang$maxFixedArity = 3;
G__8008.cljs$lang$applyTo = (function (arglist__8009){
var x = cljs.core.first(arglist__8009);
var y = cljs.core.first(cljs.core.next(arglist__8009));
var z = cljs.core.first(cljs.core.next(cljs.core.next(arglist__8009)));
var args = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__8009)));
return G__8008__delegate(x, y, z, args);
});
G__8008.cljs$lang$arity$variadic = G__8008__delegate;
return G__8008;
})()
;
ep3 = function(x,y,z,var_args){
var args = var_args;
switch(arguments.length){
case 0:
return ep3__0.call(this);
case 1:
return ep3__1.call(this,x);
case 2:
return ep3__2.call(this,x,y);
case 3:
return ep3__3.call(this,x,y,z);
default:
return ep3__4.cljs$lang$arity$variadic(x,y,z, cljs.core.array_seq(arguments, 3));
}
throw('Invalid arity: ' + arguments.length);
};
ep3.cljs$lang$maxFixedArity = 3;
ep3.cljs$lang$applyTo = ep3__4.cljs$lang$applyTo;
ep3.cljs$lang$arity$0 = ep3__0;
ep3.cljs$lang$arity$1 = ep3__1;
ep3.cljs$lang$arity$2 = ep3__2;
ep3.cljs$lang$arity$3 = ep3__3;
ep3.cljs$lang$arity$variadic = ep3__4.cljs$lang$arity$variadic;
return ep3;
})()
});
var every_pred__4 = (function() { 
var G__8010__delegate = function (p1,p2,p3,ps){
var ps__7995 = cljs.core.list_STAR_.call(null,p1,p2,p3,ps);
return (function() {
var epn = null;
var epn__0 = (function (){
return true;
});
var epn__1 = (function (x){
return cljs.core.every_QMARK_.call(null,(function (p1__7805_SHARP_){
return p1__7805_SHARP_.call(null,x);
}),ps__7995);
});
var epn__2 = (function (x,y){
return cljs.core.every_QMARK_.call(null,(function (p1__7806_SHARP_){
var and__3822__auto____8000 = p1__7806_SHARP_.call(null,x);
if(cljs.core.truth_(and__3822__auto____8000))
{return p1__7806_SHARP_.call(null,y);
} else
{return and__3822__auto____8000;
}
}),ps__7995);
});
var epn__3 = (function (x,y,z){
return cljs.core.every_QMARK_.call(null,(function (p1__7807_SHARP_){
var and__3822__auto____8001 = p1__7807_SHARP_.call(null,x);
if(cljs.core.truth_(and__3822__auto____8001))
{var and__3822__auto____8002 = p1__7807_SHARP_.call(null,y);
if(cljs.core.truth_(and__3822__auto____8002))
{return p1__7807_SHARP_.call(null,z);
} else
{return and__3822__auto____8002;
}
} else
{return and__3822__auto____8001;
}
}),ps__7995);
});
var epn__4 = (function() { 
var G__8011__delegate = function (x,y,z,args){
return cljs.core.boolean$.call(null,(function (){var and__3822__auto____8003 = epn.call(null,x,y,z);
if(cljs.core.truth_(and__3822__auto____8003))
{return cljs.core.every_QMARK_.call(null,(function (p1__7808_SHARP_){
return cljs.core.every_QMARK_.call(null,p1__7808_SHARP_,args);
}),ps__7995);
} else
{return and__3822__auto____8003;
}
})());
};
var G__8011 = function (x,y,z,var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return G__8011__delegate.call(this, x, y, z, args);
};
G__8011.cljs$lang$maxFixedArity = 3;
G__8011.cljs$lang$applyTo = (function (arglist__8012){
var x = cljs.core.first(arglist__8012);
var y = cljs.core.first(cljs.core.next(arglist__8012));
var z = cljs.core.first(cljs.core.next(cljs.core.next(arglist__8012)));
var args = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__8012)));
return G__8011__delegate(x, y, z, args);
});
G__8011.cljs$lang$arity$variadic = G__8011__delegate;
return G__8011;
})()
;
epn = function(x,y,z,var_args){
var args = var_args;
switch(arguments.length){
case 0:
return epn__0.call(this);
case 1:
return epn__1.call(this,x);
case 2:
return epn__2.call(this,x,y);
case 3:
return epn__3.call(this,x,y,z);
default:
return epn__4.cljs$lang$arity$variadic(x,y,z, cljs.core.array_seq(arguments, 3));
}
throw('Invalid arity: ' + arguments.length);
};
epn.cljs$lang$maxFixedArity = 3;
epn.cljs$lang$applyTo = epn__4.cljs$lang$applyTo;
epn.cljs$lang$arity$0 = epn__0;
epn.cljs$lang$arity$1 = epn__1;
epn.cljs$lang$arity$2 = epn__2;
epn.cljs$lang$arity$3 = epn__3;
epn.cljs$lang$arity$variadic = epn__4.cljs$lang$arity$variadic;
return epn;
})()
};
var G__8010 = function (p1,p2,p3,var_args){
var ps = null;
if (goog.isDef(var_args)) {
  ps = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return G__8010__delegate.call(this, p1, p2, p3, ps);
};
G__8010.cljs$lang$maxFixedArity = 3;
G__8010.cljs$lang$applyTo = (function (arglist__8013){
var p1 = cljs.core.first(arglist__8013);
var p2 = cljs.core.first(cljs.core.next(arglist__8013));
var p3 = cljs.core.first(cljs.core.next(cljs.core.next(arglist__8013)));
var ps = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__8013)));
return G__8010__delegate(p1, p2, p3, ps);
});
G__8010.cljs$lang$arity$variadic = G__8010__delegate;
return G__8010;
})()
;
every_pred = function(p1,p2,p3,var_args){
var ps = var_args;
switch(arguments.length){
case 1:
return every_pred__1.call(this,p1);
case 2:
return every_pred__2.call(this,p1,p2);
case 3:
return every_pred__3.call(this,p1,p2,p3);
default:
return every_pred__4.cljs$lang$arity$variadic(p1,p2,p3, cljs.core.array_seq(arguments, 3));
}
throw('Invalid arity: ' + arguments.length);
};
every_pred.cljs$lang$maxFixedArity = 3;
every_pred.cljs$lang$applyTo = every_pred__4.cljs$lang$applyTo;
every_pred.cljs$lang$arity$1 = every_pred__1;
every_pred.cljs$lang$arity$2 = every_pred__2;
every_pred.cljs$lang$arity$3 = every_pred__3;
every_pred.cljs$lang$arity$variadic = every_pred__4.cljs$lang$arity$variadic;
return every_pred;
})()
;
/**
* Takes a set of predicates and returns a function f that returns the first logical true value
* returned by one of its composing predicates against any of its arguments, else it returns
* logical false. Note that f is short-circuiting in that it will stop execution on the first
* argument that triggers a logical true result against the original predicates.
* @param {...*} var_args
*/
cljs.core.some_fn = (function() {
var some_fn = null;
var some_fn__1 = (function (p){
return (function() {
var sp1 = null;
var sp1__0 = (function (){
return null;
});
var sp1__1 = (function (x){
return p.call(null,x);
});
var sp1__2 = (function (x,y){
var or__3824__auto____8094 = p.call(null,x);
if(cljs.core.truth_(or__3824__auto____8094))
{return or__3824__auto____8094;
} else
{return p.call(null,y);
}
});
var sp1__3 = (function (x,y,z){
var or__3824__auto____8095 = p.call(null,x);
if(cljs.core.truth_(or__3824__auto____8095))
{return or__3824__auto____8095;
} else
{var or__3824__auto____8096 = p.call(null,y);
if(cljs.core.truth_(or__3824__auto____8096))
{return or__3824__auto____8096;
} else
{return p.call(null,z);
}
}
});
var sp1__4 = (function() { 
var G__8165__delegate = function (x,y,z,args){
var or__3824__auto____8097 = sp1.call(null,x,y,z);
if(cljs.core.truth_(or__3824__auto____8097))
{return or__3824__auto____8097;
} else
{return cljs.core.some.call(null,p,args);
}
};
var G__8165 = function (x,y,z,var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return G__8165__delegate.call(this, x, y, z, args);
};
G__8165.cljs$lang$maxFixedArity = 3;
G__8165.cljs$lang$applyTo = (function (arglist__8166){
var x = cljs.core.first(arglist__8166);
var y = cljs.core.first(cljs.core.next(arglist__8166));
var z = cljs.core.first(cljs.core.next(cljs.core.next(arglist__8166)));
var args = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__8166)));
return G__8165__delegate(x, y, z, args);
});
G__8165.cljs$lang$arity$variadic = G__8165__delegate;
return G__8165;
})()
;
sp1 = function(x,y,z,var_args){
var args = var_args;
switch(arguments.length){
case 0:
return sp1__0.call(this);
case 1:
return sp1__1.call(this,x);
case 2:
return sp1__2.call(this,x,y);
case 3:
return sp1__3.call(this,x,y,z);
default:
return sp1__4.cljs$lang$arity$variadic(x,y,z, cljs.core.array_seq(arguments, 3));
}
throw('Invalid arity: ' + arguments.length);
};
sp1.cljs$lang$maxFixedArity = 3;
sp1.cljs$lang$applyTo = sp1__4.cljs$lang$applyTo;
sp1.cljs$lang$arity$0 = sp1__0;
sp1.cljs$lang$arity$1 = sp1__1;
sp1.cljs$lang$arity$2 = sp1__2;
sp1.cljs$lang$arity$3 = sp1__3;
sp1.cljs$lang$arity$variadic = sp1__4.cljs$lang$arity$variadic;
return sp1;
})()
});
var some_fn__2 = (function (p1,p2){
return (function() {
var sp2 = null;
var sp2__0 = (function (){
return null;
});
var sp2__1 = (function (x){
var or__3824__auto____8109 = p1.call(null,x);
if(cljs.core.truth_(or__3824__auto____8109))
{return or__3824__auto____8109;
} else
{return p2.call(null,x);
}
});
var sp2__2 = (function (x,y){
var or__3824__auto____8110 = p1.call(null,x);
if(cljs.core.truth_(or__3824__auto____8110))
{return or__3824__auto____8110;
} else
{var or__3824__auto____8111 = p1.call(null,y);
if(cljs.core.truth_(or__3824__auto____8111))
{return or__3824__auto____8111;
} else
{var or__3824__auto____8112 = p2.call(null,x);
if(cljs.core.truth_(or__3824__auto____8112))
{return or__3824__auto____8112;
} else
{return p2.call(null,y);
}
}
}
});
var sp2__3 = (function (x,y,z){
var or__3824__auto____8113 = p1.call(null,x);
if(cljs.core.truth_(or__3824__auto____8113))
{return or__3824__auto____8113;
} else
{var or__3824__auto____8114 = p1.call(null,y);
if(cljs.core.truth_(or__3824__auto____8114))
{return or__3824__auto____8114;
} else
{var or__3824__auto____8115 = p1.call(null,z);
if(cljs.core.truth_(or__3824__auto____8115))
{return or__3824__auto____8115;
} else
{var or__3824__auto____8116 = p2.call(null,x);
if(cljs.core.truth_(or__3824__auto____8116))
{return or__3824__auto____8116;
} else
{var or__3824__auto____8117 = p2.call(null,y);
if(cljs.core.truth_(or__3824__auto____8117))
{return or__3824__auto____8117;
} else
{return p2.call(null,z);
}
}
}
}
}
});
var sp2__4 = (function() { 
var G__8167__delegate = function (x,y,z,args){
var or__3824__auto____8118 = sp2.call(null,x,y,z);
if(cljs.core.truth_(or__3824__auto____8118))
{return or__3824__auto____8118;
} else
{return cljs.core.some.call(null,(function (p1__7848_SHARP_){
var or__3824__auto____8119 = p1.call(null,p1__7848_SHARP_);
if(cljs.core.truth_(or__3824__auto____8119))
{return or__3824__auto____8119;
} else
{return p2.call(null,p1__7848_SHARP_);
}
}),args);
}
};
var G__8167 = function (x,y,z,var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return G__8167__delegate.call(this, x, y, z, args);
};
G__8167.cljs$lang$maxFixedArity = 3;
G__8167.cljs$lang$applyTo = (function (arglist__8168){
var x = cljs.core.first(arglist__8168);
var y = cljs.core.first(cljs.core.next(arglist__8168));
var z = cljs.core.first(cljs.core.next(cljs.core.next(arglist__8168)));
var args = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__8168)));
return G__8167__delegate(x, y, z, args);
});
G__8167.cljs$lang$arity$variadic = G__8167__delegate;
return G__8167;
})()
;
sp2 = function(x,y,z,var_args){
var args = var_args;
switch(arguments.length){
case 0:
return sp2__0.call(this);
case 1:
return sp2__1.call(this,x);
case 2:
return sp2__2.call(this,x,y);
case 3:
return sp2__3.call(this,x,y,z);
default:
return sp2__4.cljs$lang$arity$variadic(x,y,z, cljs.core.array_seq(arguments, 3));
}
throw('Invalid arity: ' + arguments.length);
};
sp2.cljs$lang$maxFixedArity = 3;
sp2.cljs$lang$applyTo = sp2__4.cljs$lang$applyTo;
sp2.cljs$lang$arity$0 = sp2__0;
sp2.cljs$lang$arity$1 = sp2__1;
sp2.cljs$lang$arity$2 = sp2__2;
sp2.cljs$lang$arity$3 = sp2__3;
sp2.cljs$lang$arity$variadic = sp2__4.cljs$lang$arity$variadic;
return sp2;
})()
});
var some_fn__3 = (function (p1,p2,p3){
return (function() {
var sp3 = null;
var sp3__0 = (function (){
return null;
});
var sp3__1 = (function (x){
var or__3824__auto____8138 = p1.call(null,x);
if(cljs.core.truth_(or__3824__auto____8138))
{return or__3824__auto____8138;
} else
{var or__3824__auto____8139 = p2.call(null,x);
if(cljs.core.truth_(or__3824__auto____8139))
{return or__3824__auto____8139;
} else
{return p3.call(null,x);
}
}
});
var sp3__2 = (function (x,y){
var or__3824__auto____8140 = p1.call(null,x);
if(cljs.core.truth_(or__3824__auto____8140))
{return or__3824__auto____8140;
} else
{var or__3824__auto____8141 = p2.call(null,x);
if(cljs.core.truth_(or__3824__auto____8141))
{return or__3824__auto____8141;
} else
{var or__3824__auto____8142 = p3.call(null,x);
if(cljs.core.truth_(or__3824__auto____8142))
{return or__3824__auto____8142;
} else
{var or__3824__auto____8143 = p1.call(null,y);
if(cljs.core.truth_(or__3824__auto____8143))
{return or__3824__auto____8143;
} else
{var or__3824__auto____8144 = p2.call(null,y);
if(cljs.core.truth_(or__3824__auto____8144))
{return or__3824__auto____8144;
} else
{return p3.call(null,y);
}
}
}
}
}
});
var sp3__3 = (function (x,y,z){
var or__3824__auto____8145 = p1.call(null,x);
if(cljs.core.truth_(or__3824__auto____8145))
{return or__3824__auto____8145;
} else
{var or__3824__auto____8146 = p2.call(null,x);
if(cljs.core.truth_(or__3824__auto____8146))
{return or__3824__auto____8146;
} else
{var or__3824__auto____8147 = p3.call(null,x);
if(cljs.core.truth_(or__3824__auto____8147))
{return or__3824__auto____8147;
} else
{var or__3824__auto____8148 = p1.call(null,y);
if(cljs.core.truth_(or__3824__auto____8148))
{return or__3824__auto____8148;
} else
{var or__3824__auto____8149 = p2.call(null,y);
if(cljs.core.truth_(or__3824__auto____8149))
{return or__3824__auto____8149;
} else
{var or__3824__auto____8150 = p3.call(null,y);
if(cljs.core.truth_(or__3824__auto____8150))
{return or__3824__auto____8150;
} else
{var or__3824__auto____8151 = p1.call(null,z);
if(cljs.core.truth_(or__3824__auto____8151))
{return or__3824__auto____8151;
} else
{var or__3824__auto____8152 = p2.call(null,z);
if(cljs.core.truth_(or__3824__auto____8152))
{return or__3824__auto____8152;
} else
{return p3.call(null,z);
}
}
}
}
}
}
}
}
});
var sp3__4 = (function() { 
var G__8169__delegate = function (x,y,z,args){
var or__3824__auto____8153 = sp3.call(null,x,y,z);
if(cljs.core.truth_(or__3824__auto____8153))
{return or__3824__auto____8153;
} else
{return cljs.core.some.call(null,(function (p1__7849_SHARP_){
var or__3824__auto____8154 = p1.call(null,p1__7849_SHARP_);
if(cljs.core.truth_(or__3824__auto____8154))
{return or__3824__auto____8154;
} else
{var or__3824__auto____8155 = p2.call(null,p1__7849_SHARP_);
if(cljs.core.truth_(or__3824__auto____8155))
{return or__3824__auto____8155;
} else
{return p3.call(null,p1__7849_SHARP_);
}
}
}),args);
}
};
var G__8169 = function (x,y,z,var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return G__8169__delegate.call(this, x, y, z, args);
};
G__8169.cljs$lang$maxFixedArity = 3;
G__8169.cljs$lang$applyTo = (function (arglist__8170){
var x = cljs.core.first(arglist__8170);
var y = cljs.core.first(cljs.core.next(arglist__8170));
var z = cljs.core.first(cljs.core.next(cljs.core.next(arglist__8170)));
var args = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__8170)));
return G__8169__delegate(x, y, z, args);
});
G__8169.cljs$lang$arity$variadic = G__8169__delegate;
return G__8169;
})()
;
sp3 = function(x,y,z,var_args){
var args = var_args;
switch(arguments.length){
case 0:
return sp3__0.call(this);
case 1:
return sp3__1.call(this,x);
case 2:
return sp3__2.call(this,x,y);
case 3:
return sp3__3.call(this,x,y,z);
default:
return sp3__4.cljs$lang$arity$variadic(x,y,z, cljs.core.array_seq(arguments, 3));
}
throw('Invalid arity: ' + arguments.length);
};
sp3.cljs$lang$maxFixedArity = 3;
sp3.cljs$lang$applyTo = sp3__4.cljs$lang$applyTo;
sp3.cljs$lang$arity$0 = sp3__0;
sp3.cljs$lang$arity$1 = sp3__1;
sp3.cljs$lang$arity$2 = sp3__2;
sp3.cljs$lang$arity$3 = sp3__3;
sp3.cljs$lang$arity$variadic = sp3__4.cljs$lang$arity$variadic;
return sp3;
})()
});
var some_fn__4 = (function() { 
var G__8171__delegate = function (p1,p2,p3,ps){
var ps__8156 = cljs.core.list_STAR_.call(null,p1,p2,p3,ps);
return (function() {
var spn = null;
var spn__0 = (function (){
return null;
});
var spn__1 = (function (x){
return cljs.core.some.call(null,(function (p1__7850_SHARP_){
return p1__7850_SHARP_.call(null,x);
}),ps__8156);
});
var spn__2 = (function (x,y){
return cljs.core.some.call(null,(function (p1__7851_SHARP_){
var or__3824__auto____8161 = p1__7851_SHARP_.call(null,x);
if(cljs.core.truth_(or__3824__auto____8161))
{return or__3824__auto____8161;
} else
{return p1__7851_SHARP_.call(null,y);
}
}),ps__8156);
});
var spn__3 = (function (x,y,z){
return cljs.core.some.call(null,(function (p1__7852_SHARP_){
var or__3824__auto____8162 = p1__7852_SHARP_.call(null,x);
if(cljs.core.truth_(or__3824__auto____8162))
{return or__3824__auto____8162;
} else
{var or__3824__auto____8163 = p1__7852_SHARP_.call(null,y);
if(cljs.core.truth_(or__3824__auto____8163))
{return or__3824__auto____8163;
} else
{return p1__7852_SHARP_.call(null,z);
}
}
}),ps__8156);
});
var spn__4 = (function() { 
var G__8172__delegate = function (x,y,z,args){
var or__3824__auto____8164 = spn.call(null,x,y,z);
if(cljs.core.truth_(or__3824__auto____8164))
{return or__3824__auto____8164;
} else
{return cljs.core.some.call(null,(function (p1__7853_SHARP_){
return cljs.core.some.call(null,p1__7853_SHARP_,args);
}),ps__8156);
}
};
var G__8172 = function (x,y,z,var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return G__8172__delegate.call(this, x, y, z, args);
};
G__8172.cljs$lang$maxFixedArity = 3;
G__8172.cljs$lang$applyTo = (function (arglist__8173){
var x = cljs.core.first(arglist__8173);
var y = cljs.core.first(cljs.core.next(arglist__8173));
var z = cljs.core.first(cljs.core.next(cljs.core.next(arglist__8173)));
var args = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__8173)));
return G__8172__delegate(x, y, z, args);
});
G__8172.cljs$lang$arity$variadic = G__8172__delegate;
return G__8172;
})()
;
spn = function(x,y,z,var_args){
var args = var_args;
switch(arguments.length){
case 0:
return spn__0.call(this);
case 1:
return spn__1.call(this,x);
case 2:
return spn__2.call(this,x,y);
case 3:
return spn__3.call(this,x,y,z);
default:
return spn__4.cljs$lang$arity$variadic(x,y,z, cljs.core.array_seq(arguments, 3));
}
throw('Invalid arity: ' + arguments.length);
};
spn.cljs$lang$maxFixedArity = 3;
spn.cljs$lang$applyTo = spn__4.cljs$lang$applyTo;
spn.cljs$lang$arity$0 = spn__0;
spn.cljs$lang$arity$1 = spn__1;
spn.cljs$lang$arity$2 = spn__2;
spn.cljs$lang$arity$3 = spn__3;
spn.cljs$lang$arity$variadic = spn__4.cljs$lang$arity$variadic;
return spn;
})()
};
var G__8171 = function (p1,p2,p3,var_args){
var ps = null;
if (goog.isDef(var_args)) {
  ps = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return G__8171__delegate.call(this, p1, p2, p3, ps);
};
G__8171.cljs$lang$maxFixedArity = 3;
G__8171.cljs$lang$applyTo = (function (arglist__8174){
var p1 = cljs.core.first(arglist__8174);
var p2 = cljs.core.first(cljs.core.next(arglist__8174));
var p3 = cljs.core.first(cljs.core.next(cljs.core.next(arglist__8174)));
var ps = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__8174)));
return G__8171__delegate(p1, p2, p3, ps);
});
G__8171.cljs$lang$arity$variadic = G__8171__delegate;
return G__8171;
})()
;
some_fn = function(p1,p2,p3,var_args){
var ps = var_args;
switch(arguments.length){
case 1:
return some_fn__1.call(this,p1);
case 2:
return some_fn__2.call(this,p1,p2);
case 3:
return some_fn__3.call(this,p1,p2,p3);
default:
return some_fn__4.cljs$lang$arity$variadic(p1,p2,p3, cljs.core.array_seq(arguments, 3));
}
throw('Invalid arity: ' + arguments.length);
};
some_fn.cljs$lang$maxFixedArity = 3;
some_fn.cljs$lang$applyTo = some_fn__4.cljs$lang$applyTo;
some_fn.cljs$lang$arity$1 = some_fn__1;
some_fn.cljs$lang$arity$2 = some_fn__2;
some_fn.cljs$lang$arity$3 = some_fn__3;
some_fn.cljs$lang$arity$variadic = some_fn__4.cljs$lang$arity$variadic;
return some_fn;
})()
;
/**
* Returns a lazy sequence consisting of the result of applying f to the
* set of first items of each coll, followed by applying f to the set
* of second items in each coll, until any one of the colls is
* exhausted.  Any remaining items in other colls are ignored. Function
* f should accept number-of-colls arguments.
* @param {...*} var_args
*/
cljs.core.map = (function() {
var map = null;
var map__2 = (function (f,coll){
return (new cljs.core.LazySeq(null,false,(function (){
var temp__3974__auto____8193 = cljs.core.seq.call(null,coll);
if(temp__3974__auto____8193)
{var s__8194 = temp__3974__auto____8193;
if(cljs.core.chunked_seq_QMARK_.call(null,s__8194))
{var c__8195 = cljs.core.chunk_first.call(null,s__8194);
var size__8196 = cljs.core.count.call(null,c__8195);
var b__8197 = cljs.core.chunk_buffer.call(null,size__8196);
var n__2555__auto____8198 = size__8196;
var i__8199 = 0;
while(true){
if((i__8199 < n__2555__auto____8198))
{cljs.core.chunk_append.call(null,b__8197,f.call(null,cljs.core._nth.call(null,c__8195,i__8199)));
{
var G__8211 = (i__8199 + 1);
i__8199 = G__8211;
continue;
}
} else
{}
break;
}
return cljs.core.chunk_cons.call(null,cljs.core.chunk.call(null,b__8197),map.call(null,f,cljs.core.chunk_rest.call(null,s__8194)));
} else
{return cljs.core.cons.call(null,f.call(null,cljs.core.first.call(null,s__8194)),map.call(null,f,cljs.core.rest.call(null,s__8194)));
}
} else
{return null;
}
}),null));
});
var map__3 = (function (f,c1,c2){
return (new cljs.core.LazySeq(null,false,(function (){
var s1__8200 = cljs.core.seq.call(null,c1);
var s2__8201 = cljs.core.seq.call(null,c2);
if((function (){var and__3822__auto____8202 = s1__8200;
if(and__3822__auto____8202)
{return s2__8201;
} else
{return and__3822__auto____8202;
}
})())
{return cljs.core.cons.call(null,f.call(null,cljs.core.first.call(null,s1__8200),cljs.core.first.call(null,s2__8201)),map.call(null,f,cljs.core.rest.call(null,s1__8200),cljs.core.rest.call(null,s2__8201)));
} else
{return null;
}
}),null));
});
var map__4 = (function (f,c1,c2,c3){
return (new cljs.core.LazySeq(null,false,(function (){
var s1__8203 = cljs.core.seq.call(null,c1);
var s2__8204 = cljs.core.seq.call(null,c2);
var s3__8205 = cljs.core.seq.call(null,c3);
if((function (){var and__3822__auto____8206 = s1__8203;
if(and__3822__auto____8206)
{var and__3822__auto____8207 = s2__8204;
if(and__3822__auto____8207)
{return s3__8205;
} else
{return and__3822__auto____8207;
}
} else
{return and__3822__auto____8206;
}
})())
{return cljs.core.cons.call(null,f.call(null,cljs.core.first.call(null,s1__8203),cljs.core.first.call(null,s2__8204),cljs.core.first.call(null,s3__8205)),map.call(null,f,cljs.core.rest.call(null,s1__8203),cljs.core.rest.call(null,s2__8204),cljs.core.rest.call(null,s3__8205)));
} else
{return null;
}
}),null));
});
var map__5 = (function() { 
var G__8212__delegate = function (f,c1,c2,c3,colls){
var step__8210 = (function step(cs){
return (new cljs.core.LazySeq(null,false,(function (){
var ss__8209 = map.call(null,cljs.core.seq,cs);
if(cljs.core.every_QMARK_.call(null,cljs.core.identity,ss__8209))
{return cljs.core.cons.call(null,map.call(null,cljs.core.first,ss__8209),step.call(null,map.call(null,cljs.core.rest,ss__8209)));
} else
{return null;
}
}),null));
});
return map.call(null,(function (p1__8014_SHARP_){
return cljs.core.apply.call(null,f,p1__8014_SHARP_);
}),step__8210.call(null,cljs.core.conj.call(null,colls,c3,c2,c1)));
};
var G__8212 = function (f,c1,c2,c3,var_args){
var colls = null;
if (goog.isDef(var_args)) {
  colls = cljs.core.array_seq(Array.prototype.slice.call(arguments, 4),0);
} 
return G__8212__delegate.call(this, f, c1, c2, c3, colls);
};
G__8212.cljs$lang$maxFixedArity = 4;
G__8212.cljs$lang$applyTo = (function (arglist__8213){
var f = cljs.core.first(arglist__8213);
var c1 = cljs.core.first(cljs.core.next(arglist__8213));
var c2 = cljs.core.first(cljs.core.next(cljs.core.next(arglist__8213)));
var c3 = cljs.core.first(cljs.core.next(cljs.core.next(cljs.core.next(arglist__8213))));
var colls = cljs.core.rest(cljs.core.next(cljs.core.next(cljs.core.next(arglist__8213))));
return G__8212__delegate(f, c1, c2, c3, colls);
});
G__8212.cljs$lang$arity$variadic = G__8212__delegate;
return G__8212;
})()
;
map = function(f,c1,c2,c3,var_args){
var colls = var_args;
switch(arguments.length){
case 2:
return map__2.call(this,f,c1);
case 3:
return map__3.call(this,f,c1,c2);
case 4:
return map__4.call(this,f,c1,c2,c3);
default:
return map__5.cljs$lang$arity$variadic(f,c1,c2,c3, cljs.core.array_seq(arguments, 4));
}
throw('Invalid arity: ' + arguments.length);
};
map.cljs$lang$maxFixedArity = 4;
map.cljs$lang$applyTo = map__5.cljs$lang$applyTo;
map.cljs$lang$arity$2 = map__2;
map.cljs$lang$arity$3 = map__3;
map.cljs$lang$arity$4 = map__4;
map.cljs$lang$arity$variadic = map__5.cljs$lang$arity$variadic;
return map;
})()
;
/**
* Returns a lazy sequence of the first n items in coll, or all items if
* there are fewer than n.
*/
cljs.core.take = (function take(n,coll){
return (new cljs.core.LazySeq(null,false,(function (){
if((n > 0))
{var temp__3974__auto____8216 = cljs.core.seq.call(null,coll);
if(temp__3974__auto____8216)
{var s__8217 = temp__3974__auto____8216;
return cljs.core.cons.call(null,cljs.core.first.call(null,s__8217),take.call(null,(n - 1),cljs.core.rest.call(null,s__8217)));
} else
{return null;
}
} else
{return null;
}
}),null));
});
/**
* Returns a lazy sequence of all but the first n items in coll.
*/
cljs.core.drop = (function drop(n,coll){
var step__8223 = (function (n,coll){
while(true){
var s__8221 = cljs.core.seq.call(null,coll);
if(cljs.core.truth_((function (){var and__3822__auto____8222 = (n > 0);
if(and__3822__auto____8222)
{return s__8221;
} else
{return and__3822__auto____8222;
}
})()))
{{
var G__8224 = (n - 1);
var G__8225 = cljs.core.rest.call(null,s__8221);
n = G__8224;
coll = G__8225;
continue;
}
} else
{return s__8221;
}
break;
}
});
return (new cljs.core.LazySeq(null,false,(function (){
return step__8223.call(null,n,coll);
}),null));
});
/**
* Return a lazy sequence of all but the last n (default 1) items in coll
*/
cljs.core.drop_last = (function() {
var drop_last = null;
var drop_last__1 = (function (s){
return drop_last.call(null,1,s);
});
var drop_last__2 = (function (n,s){
return cljs.core.map.call(null,(function (x,_){
return x;
}),s,cljs.core.drop.call(null,n,s));
});
drop_last = function(n,s){
switch(arguments.length){
case 1:
return drop_last__1.call(this,n);
case 2:
return drop_last__2.call(this,n,s);
}
throw('Invalid arity: ' + arguments.length);
};
drop_last.cljs$lang$arity$1 = drop_last__1;
drop_last.cljs$lang$arity$2 = drop_last__2;
return drop_last;
})()
;
/**
* Returns a seq of the last n items in coll.  Depending on the type
* of coll may be no better than linear time.  For vectors, see also subvec.
*/
cljs.core.take_last = (function take_last(n,coll){
var s__8228 = cljs.core.seq.call(null,coll);
var lead__8229 = cljs.core.seq.call(null,cljs.core.drop.call(null,n,coll));
while(true){
if(lead__8229)
{{
var G__8230 = cljs.core.next.call(null,s__8228);
var G__8231 = cljs.core.next.call(null,lead__8229);
s__8228 = G__8230;
lead__8229 = G__8231;
continue;
}
} else
{return s__8228;
}
break;
}
});
/**
* Returns a lazy sequence of the items in coll starting from the first
* item for which (pred item) returns nil.
*/
cljs.core.drop_while = (function drop_while(pred,coll){
var step__8237 = (function (pred,coll){
while(true){
var s__8235 = cljs.core.seq.call(null,coll);
if(cljs.core.truth_((function (){var and__3822__auto____8236 = s__8235;
if(and__3822__auto____8236)
{return pred.call(null,cljs.core.first.call(null,s__8235));
} else
{return and__3822__auto____8236;
}
})()))
{{
var G__8238 = pred;
var G__8239 = cljs.core.rest.call(null,s__8235);
pred = G__8238;
coll = G__8239;
continue;
}
} else
{return s__8235;
}
break;
}
});
return (new cljs.core.LazySeq(null,false,(function (){
return step__8237.call(null,pred,coll);
}),null));
});
/**
* Returns a lazy (infinite!) sequence of repetitions of the items in coll.
*/
cljs.core.cycle = (function cycle(coll){
return (new cljs.core.LazySeq(null,false,(function (){
var temp__3974__auto____8242 = cljs.core.seq.call(null,coll);
if(temp__3974__auto____8242)
{var s__8243 = temp__3974__auto____8242;
return cljs.core.concat.call(null,s__8243,cycle.call(null,s__8243));
} else
{return null;
}
}),null));
});
/**
* Returns a vector of [(take n coll) (drop n coll)]
*/
cljs.core.split_at = (function split_at(n,coll){
return cljs.core.PersistentVector.fromArray([cljs.core.take.call(null,n,coll),cljs.core.drop.call(null,n,coll)], true);
});
/**
* Returns a lazy (infinite!, or length n if supplied) sequence of xs.
*/
cljs.core.repeat = (function() {
var repeat = null;
var repeat__1 = (function (x){
return (new cljs.core.LazySeq(null,false,(function (){
return cljs.core.cons.call(null,x,repeat.call(null,x));
}),null));
});
var repeat__2 = (function (n,x){
return cljs.core.take.call(null,n,repeat.call(null,x));
});
repeat = function(n,x){
switch(arguments.length){
case 1:
return repeat__1.call(this,n);
case 2:
return repeat__2.call(this,n,x);
}
throw('Invalid arity: ' + arguments.length);
};
repeat.cljs$lang$arity$1 = repeat__1;
repeat.cljs$lang$arity$2 = repeat__2;
return repeat;
})()
;
/**
* Returns a lazy seq of n xs.
*/
cljs.core.replicate = (function replicate(n,x){
return cljs.core.take.call(null,n,cljs.core.repeat.call(null,x));
});
/**
* Takes a function of no args, presumably with side effects, and
* returns an infinite (or length n if supplied) lazy sequence of calls
* to it
*/
cljs.core.repeatedly = (function() {
var repeatedly = null;
var repeatedly__1 = (function (f){
return (new cljs.core.LazySeq(null,false,(function (){
return cljs.core.cons.call(null,f.call(null),repeatedly.call(null,f));
}),null));
});
var repeatedly__2 = (function (n,f){
return cljs.core.take.call(null,n,repeatedly.call(null,f));
});
repeatedly = function(n,f){
switch(arguments.length){
case 1:
return repeatedly__1.call(this,n);
case 2:
return repeatedly__2.call(this,n,f);
}
throw('Invalid arity: ' + arguments.length);
};
repeatedly.cljs$lang$arity$1 = repeatedly__1;
repeatedly.cljs$lang$arity$2 = repeatedly__2;
return repeatedly;
})()
;
/**
* Returns a lazy sequence of x, (f x), (f (f x)) etc. f must be free of side-effects
*/
cljs.core.iterate = (function iterate(f,x){
return cljs.core.cons.call(null,x,(new cljs.core.LazySeq(null,false,(function (){
return iterate.call(null,f,f.call(null,x));
}),null)));
});
/**
* Returns a lazy seq of the first item in each coll, then the second etc.
* @param {...*} var_args
*/
cljs.core.interleave = (function() {
var interleave = null;
var interleave__2 = (function (c1,c2){
return (new cljs.core.LazySeq(null,false,(function (){
var s1__8248 = cljs.core.seq.call(null,c1);
var s2__8249 = cljs.core.seq.call(null,c2);
if((function (){var and__3822__auto____8250 = s1__8248;
if(and__3822__auto____8250)
{return s2__8249;
} else
{return and__3822__auto____8250;
}
})())
{return cljs.core.cons.call(null,cljs.core.first.call(null,s1__8248),cljs.core.cons.call(null,cljs.core.first.call(null,s2__8249),interleave.call(null,cljs.core.rest.call(null,s1__8248),cljs.core.rest.call(null,s2__8249))));
} else
{return null;
}
}),null));
});
var interleave__3 = (function() { 
var G__8252__delegate = function (c1,c2,colls){
return (new cljs.core.LazySeq(null,false,(function (){
var ss__8251 = cljs.core.map.call(null,cljs.core.seq,cljs.core.conj.call(null,colls,c2,c1));
if(cljs.core.every_QMARK_.call(null,cljs.core.identity,ss__8251))
{return cljs.core.concat.call(null,cljs.core.map.call(null,cljs.core.first,ss__8251),cljs.core.apply.call(null,interleave,cljs.core.map.call(null,cljs.core.rest,ss__8251)));
} else
{return null;
}
}),null));
};
var G__8252 = function (c1,c2,var_args){
var colls = null;
if (goog.isDef(var_args)) {
  colls = cljs.core.array_seq(Array.prototype.slice.call(arguments, 2),0);
} 
return G__8252__delegate.call(this, c1, c2, colls);
};
G__8252.cljs$lang$maxFixedArity = 2;
G__8252.cljs$lang$applyTo = (function (arglist__8253){
var c1 = cljs.core.first(arglist__8253);
var c2 = cljs.core.first(cljs.core.next(arglist__8253));
var colls = cljs.core.rest(cljs.core.next(arglist__8253));
return G__8252__delegate(c1, c2, colls);
});
G__8252.cljs$lang$arity$variadic = G__8252__delegate;
return G__8252;
})()
;
interleave = function(c1,c2,var_args){
var colls = var_args;
switch(arguments.length){
case 2:
return interleave__2.call(this,c1,c2);
default:
return interleave__3.cljs$lang$arity$variadic(c1,c2, cljs.core.array_seq(arguments, 2));
}
throw('Invalid arity: ' + arguments.length);
};
interleave.cljs$lang$maxFixedArity = 2;
interleave.cljs$lang$applyTo = interleave__3.cljs$lang$applyTo;
interleave.cljs$lang$arity$2 = interleave__2;
interleave.cljs$lang$arity$variadic = interleave__3.cljs$lang$arity$variadic;
return interleave;
})()
;
/**
* Returns a lazy seq of the elements of coll separated by sep
*/
cljs.core.interpose = (function interpose(sep,coll){
return cljs.core.drop.call(null,1,cljs.core.interleave.call(null,cljs.core.repeat.call(null,sep),coll));
});
/**
* Take a collection of collections, and return a lazy seq
* of items from the inner collection
*/
cljs.core.flatten1 = (function flatten1(colls){
var cat__8263 = (function cat(coll,colls){
return (new cljs.core.LazySeq(null,false,(function (){
var temp__3971__auto____8261 = cljs.core.seq.call(null,coll);
if(temp__3971__auto____8261)
{var coll__8262 = temp__3971__auto____8261;
return cljs.core.cons.call(null,cljs.core.first.call(null,coll__8262),cat.call(null,cljs.core.rest.call(null,coll__8262),colls));
} else
{if(cljs.core.seq.call(null,colls))
{return cat.call(null,cljs.core.first.call(null,colls),cljs.core.rest.call(null,colls));
} else
{return null;
}
}
}),null));
});
return cat__8263.call(null,null,colls);
});
/**
* Returns the result of applying concat to the result of applying map
* to f and colls.  Thus function f should return a collection.
* @param {...*} var_args
*/
cljs.core.mapcat = (function() {
var mapcat = null;
var mapcat__2 = (function (f,coll){
return cljs.core.flatten1.call(null,cljs.core.map.call(null,f,coll));
});
var mapcat__3 = (function() { 
var G__8264__delegate = function (f,coll,colls){
return cljs.core.flatten1.call(null,cljs.core.apply.call(null,cljs.core.map,f,coll,colls));
};
var G__8264 = function (f,coll,var_args){
var colls = null;
if (goog.isDef(var_args)) {
  colls = cljs.core.array_seq(Array.prototype.slice.call(arguments, 2),0);
} 
return G__8264__delegate.call(this, f, coll, colls);
};
G__8264.cljs$lang$maxFixedArity = 2;
G__8264.cljs$lang$applyTo = (function (arglist__8265){
var f = cljs.core.first(arglist__8265);
var coll = cljs.core.first(cljs.core.next(arglist__8265));
var colls = cljs.core.rest(cljs.core.next(arglist__8265));
return G__8264__delegate(f, coll, colls);
});
G__8264.cljs$lang$arity$variadic = G__8264__delegate;
return G__8264;
})()
;
mapcat = function(f,coll,var_args){
var colls = var_args;
switch(arguments.length){
case 2:
return mapcat__2.call(this,f,coll);
default:
return mapcat__3.cljs$lang$arity$variadic(f,coll, cljs.core.array_seq(arguments, 2));
}
throw('Invalid arity: ' + arguments.length);
};
mapcat.cljs$lang$maxFixedArity = 2;
mapcat.cljs$lang$applyTo = mapcat__3.cljs$lang$applyTo;
mapcat.cljs$lang$arity$2 = mapcat__2;
mapcat.cljs$lang$arity$variadic = mapcat__3.cljs$lang$arity$variadic;
return mapcat;
})()
;
/**
* Returns a lazy sequence of the items in coll for which
* (pred item) returns true. pred must be free of side-effects.
*/
cljs.core.filter = (function filter(pred,coll){
return (new cljs.core.LazySeq(null,false,(function (){
var temp__3974__auto____8275 = cljs.core.seq.call(null,coll);
if(temp__3974__auto____8275)
{var s__8276 = temp__3974__auto____8275;
if(cljs.core.chunked_seq_QMARK_.call(null,s__8276))
{var c__8277 = cljs.core.chunk_first.call(null,s__8276);
var size__8278 = cljs.core.count.call(null,c__8277);
var b__8279 = cljs.core.chunk_buffer.call(null,size__8278);
var n__2555__auto____8280 = size__8278;
var i__8281 = 0;
while(true){
if((i__8281 < n__2555__auto____8280))
{if(cljs.core.truth_(pred.call(null,cljs.core._nth.call(null,c__8277,i__8281))))
{cljs.core.chunk_append.call(null,b__8279,cljs.core._nth.call(null,c__8277,i__8281));
} else
{}
{
var G__8284 = (i__8281 + 1);
i__8281 = G__8284;
continue;
}
} else
{}
break;
}
return cljs.core.chunk_cons.call(null,cljs.core.chunk.call(null,b__8279),filter.call(null,pred,cljs.core.chunk_rest.call(null,s__8276)));
} else
{var f__8282 = cljs.core.first.call(null,s__8276);
var r__8283 = cljs.core.rest.call(null,s__8276);
if(cljs.core.truth_(pred.call(null,f__8282)))
{return cljs.core.cons.call(null,f__8282,filter.call(null,pred,r__8283));
} else
{return filter.call(null,pred,r__8283);
}
}
} else
{return null;
}
}),null));
});
/**
* Returns a lazy sequence of the items in coll for which
* (pred item) returns false. pred must be free of side-effects.
*/
cljs.core.remove = (function remove(pred,coll){
return cljs.core.filter.call(null,cljs.core.complement.call(null,pred),coll);
});
/**
* Returns a lazy sequence of the nodes in a tree, via a depth-first walk.
* branch? must be a fn of one arg that returns true if passed a node
* that can have children (but may not).  children must be a fn of one
* arg that returns a sequence of the children. Will only be called on
* nodes for which branch? returns true. Root is the root node of the
* tree.
*/
cljs.core.tree_seq = (function tree_seq(branch_QMARK_,children,root){
var walk__8287 = (function walk(node){
return (new cljs.core.LazySeq(null,false,(function (){
return cljs.core.cons.call(null,node,(cljs.core.truth_(branch_QMARK_.call(null,node))?cljs.core.mapcat.call(null,walk,children.call(null,node)):null));
}),null));
});
return walk__8287.call(null,root);
});
/**
* Takes any nested combination of sequential things (lists, vectors,
* etc.) and returns their contents as a single, flat sequence.
* (flatten nil) returns nil.
*/
cljs.core.flatten = (function flatten(x){
return cljs.core.filter.call(null,(function (p1__8285_SHARP_){
return !(cljs.core.sequential_QMARK_.call(null,p1__8285_SHARP_));
}),cljs.core.rest.call(null,cljs.core.tree_seq.call(null,cljs.core.sequential_QMARK_,cljs.core.seq,x)));
});
/**
* Returns a new coll consisting of to-coll with all of the items of
* from-coll conjoined.
*/
cljs.core.into = (function into(to,from){
if((function (){var G__8291__8292 = to;
if(G__8291__8292)
{if((function (){var or__3824__auto____8293 = (G__8291__8292.cljs$lang$protocol_mask$partition1$ & 1);
if(or__3824__auto____8293)
{return or__3824__auto____8293;
} else
{return G__8291__8292.cljs$core$IEditableCollection$;
}
})())
{return true;
} else
{if((!G__8291__8292.cljs$lang$protocol_mask$partition1$))
{return cljs.core.type_satisfies_.call(null,cljs.core.IEditableCollection,G__8291__8292);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.IEditableCollection,G__8291__8292);
}
})())
{return cljs.core.persistent_BANG_.call(null,cljs.core.reduce.call(null,cljs.core._conj_BANG_,cljs.core.transient$.call(null,to),from));
} else
{return cljs.core.reduce.call(null,cljs.core._conj,to,from);
}
});
/**
* Returns a vector consisting of the result of applying f to the
* set of first items of each coll, followed by applying f to the set
* of second items in each coll, until any one of the colls is
* exhausted.  Any remaining items in other colls are ignored. Function
* f should accept number-of-colls arguments.
* @param {...*} var_args
*/
cljs.core.mapv = (function() {
var mapv = null;
var mapv__2 = (function (f,coll){
return cljs.core.persistent_BANG_.call(null,cljs.core.reduce.call(null,(function (v,o){
return cljs.core.conj_BANG_.call(null,v,f.call(null,o));
}),cljs.core.transient$.call(null,cljs.core.PersistentVector.EMPTY),coll));
});
var mapv__3 = (function (f,c1,c2){
return cljs.core.into.call(null,cljs.core.PersistentVector.EMPTY,cljs.core.map.call(null,f,c1,c2));
});
var mapv__4 = (function (f,c1,c2,c3){
return cljs.core.into.call(null,cljs.core.PersistentVector.EMPTY,cljs.core.map.call(null,f,c1,c2,c3));
});
var mapv__5 = (function() { 
var G__8294__delegate = function (f,c1,c2,c3,colls){
return cljs.core.into.call(null,cljs.core.PersistentVector.EMPTY,cljs.core.apply.call(null,cljs.core.map,f,c1,c2,c3,colls));
};
var G__8294 = function (f,c1,c2,c3,var_args){
var colls = null;
if (goog.isDef(var_args)) {
  colls = cljs.core.array_seq(Array.prototype.slice.call(arguments, 4),0);
} 
return G__8294__delegate.call(this, f, c1, c2, c3, colls);
};
G__8294.cljs$lang$maxFixedArity = 4;
G__8294.cljs$lang$applyTo = (function (arglist__8295){
var f = cljs.core.first(arglist__8295);
var c1 = cljs.core.first(cljs.core.next(arglist__8295));
var c2 = cljs.core.first(cljs.core.next(cljs.core.next(arglist__8295)));
var c3 = cljs.core.first(cljs.core.next(cljs.core.next(cljs.core.next(arglist__8295))));
var colls = cljs.core.rest(cljs.core.next(cljs.core.next(cljs.core.next(arglist__8295))));
return G__8294__delegate(f, c1, c2, c3, colls);
});
G__8294.cljs$lang$arity$variadic = G__8294__delegate;
return G__8294;
})()
;
mapv = function(f,c1,c2,c3,var_args){
var colls = var_args;
switch(arguments.length){
case 2:
return mapv__2.call(this,f,c1);
case 3:
return mapv__3.call(this,f,c1,c2);
case 4:
return mapv__4.call(this,f,c1,c2,c3);
default:
return mapv__5.cljs$lang$arity$variadic(f,c1,c2,c3, cljs.core.array_seq(arguments, 4));
}
throw('Invalid arity: ' + arguments.length);
};
mapv.cljs$lang$maxFixedArity = 4;
mapv.cljs$lang$applyTo = mapv__5.cljs$lang$applyTo;
mapv.cljs$lang$arity$2 = mapv__2;
mapv.cljs$lang$arity$3 = mapv__3;
mapv.cljs$lang$arity$4 = mapv__4;
mapv.cljs$lang$arity$variadic = mapv__5.cljs$lang$arity$variadic;
return mapv;
})()
;
/**
* Returns a vector of the items in coll for which
* (pred item) returns true. pred must be free of side-effects.
*/
cljs.core.filterv = (function filterv(pred,coll){
return cljs.core.persistent_BANG_.call(null,cljs.core.reduce.call(null,(function (v,o){
if(cljs.core.truth_(pred.call(null,o)))
{return cljs.core.conj_BANG_.call(null,v,o);
} else
{return v;
}
}),cljs.core.transient$.call(null,cljs.core.PersistentVector.EMPTY),coll));
});
/**
* Returns a lazy sequence of lists of n items each, at offsets step
* apart. If step is not supplied, defaults to n, i.e. the partitions
* do not overlap. If a pad collection is supplied, use its elements as
* necessary to complete last partition upto n items. In case there are
* not enough padding elements, return a partition with less than n items.
*/
cljs.core.partition = (function() {
var partition = null;
var partition__2 = (function (n,coll){
return partition.call(null,n,n,coll);
});
var partition__3 = (function (n,step,coll){
return (new cljs.core.LazySeq(null,false,(function (){
var temp__3974__auto____8302 = cljs.core.seq.call(null,coll);
if(temp__3974__auto____8302)
{var s__8303 = temp__3974__auto____8302;
var p__8304 = cljs.core.take.call(null,n,s__8303);
if((n === cljs.core.count.call(null,p__8304)))
{return cljs.core.cons.call(null,p__8304,partition.call(null,n,step,cljs.core.drop.call(null,step,s__8303)));
} else
{return null;
}
} else
{return null;
}
}),null));
});
var partition__4 = (function (n,step,pad,coll){
return (new cljs.core.LazySeq(null,false,(function (){
var temp__3974__auto____8305 = cljs.core.seq.call(null,coll);
if(temp__3974__auto____8305)
{var s__8306 = temp__3974__auto____8305;
var p__8307 = cljs.core.take.call(null,n,s__8306);
if((n === cljs.core.count.call(null,p__8307)))
{return cljs.core.cons.call(null,p__8307,partition.call(null,n,step,pad,cljs.core.drop.call(null,step,s__8306)));
} else
{return cljs.core.list.call(null,cljs.core.take.call(null,n,cljs.core.concat.call(null,p__8307,pad)));
}
} else
{return null;
}
}),null));
});
partition = function(n,step,pad,coll){
switch(arguments.length){
case 2:
return partition__2.call(this,n,step);
case 3:
return partition__3.call(this,n,step,pad);
case 4:
return partition__4.call(this,n,step,pad,coll);
}
throw('Invalid arity: ' + arguments.length);
};
partition.cljs$lang$arity$2 = partition__2;
partition.cljs$lang$arity$3 = partition__3;
partition.cljs$lang$arity$4 = partition__4;
return partition;
})()
;
/**
* Returns the value in a nested associative structure,
* where ks is a sequence of keys. Returns nil if the key is not present,
* or the not-found value if supplied.
*/
cljs.core.get_in = (function() {
var get_in = null;
var get_in__2 = (function (m,ks){
return cljs.core.reduce.call(null,cljs.core.get,m,ks);
});
var get_in__3 = (function (m,ks,not_found){
var sentinel__8312 = cljs.core.lookup_sentinel;
var m__8313 = m;
var ks__8314 = cljs.core.seq.call(null,ks);
while(true){
if(ks__8314)
{var m__8315 = cljs.core._lookup.call(null,m__8313,cljs.core.first.call(null,ks__8314),sentinel__8312);
if((sentinel__8312 === m__8315))
{return not_found;
} else
{{
var G__8316 = sentinel__8312;
var G__8317 = m__8315;
var G__8318 = cljs.core.next.call(null,ks__8314);
sentinel__8312 = G__8316;
m__8313 = G__8317;
ks__8314 = G__8318;
continue;
}
}
} else
{return m__8313;
}
break;
}
});
get_in = function(m,ks,not_found){
switch(arguments.length){
case 2:
return get_in__2.call(this,m,ks);
case 3:
return get_in__3.call(this,m,ks,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
get_in.cljs$lang$arity$2 = get_in__2;
get_in.cljs$lang$arity$3 = get_in__3;
return get_in;
})()
;
/**
* Associates a value in a nested associative structure, where ks is a
* sequence of keys and v is the new value and returns a new nested structure.
* If any levels do not exist, hash-maps will be created.
*/
cljs.core.assoc_in = (function assoc_in(m,p__8319,v){
var vec__8324__8325 = p__8319;
var k__8326 = cljs.core.nth.call(null,vec__8324__8325,0,null);
var ks__8327 = cljs.core.nthnext.call(null,vec__8324__8325,1);
if(cljs.core.truth_(ks__8327))
{return cljs.core.assoc.call(null,m,k__8326,assoc_in.call(null,cljs.core._lookup.call(null,m,k__8326,null),ks__8327,v));
} else
{return cljs.core.assoc.call(null,m,k__8326,v);
}
});
/**
* 'Updates' a value in a nested associative structure, where ks is a
* sequence of keys and f is a function that will take the old value
* and any supplied args and return the new value, and returns a new
* nested structure.  If any levels do not exist, hash-maps will be
* created.
* @param {...*} var_args
*/
cljs.core.update_in = (function() { 
var update_in__delegate = function (m,p__8328,f,args){
var vec__8333__8334 = p__8328;
var k__8335 = cljs.core.nth.call(null,vec__8333__8334,0,null);
var ks__8336 = cljs.core.nthnext.call(null,vec__8333__8334,1);
if(cljs.core.truth_(ks__8336))
{return cljs.core.assoc.call(null,m,k__8335,cljs.core.apply.call(null,update_in,cljs.core._lookup.call(null,m,k__8335,null),ks__8336,f,args));
} else
{return cljs.core.assoc.call(null,m,k__8335,cljs.core.apply.call(null,f,cljs.core._lookup.call(null,m,k__8335,null),args));
}
};
var update_in = function (m,p__8328,f,var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return update_in__delegate.call(this, m, p__8328, f, args);
};
update_in.cljs$lang$maxFixedArity = 3;
update_in.cljs$lang$applyTo = (function (arglist__8337){
var m = cljs.core.first(arglist__8337);
var p__8328 = cljs.core.first(cljs.core.next(arglist__8337));
var f = cljs.core.first(cljs.core.next(cljs.core.next(arglist__8337)));
var args = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__8337)));
return update_in__delegate(m, p__8328, f, args);
});
update_in.cljs$lang$arity$variadic = update_in__delegate;
return update_in;
})()
;

/**
* @constructor
*/
cljs.core.Vector = (function (meta,array,__hash){
this.meta = meta;
this.array = array;
this.__hash = __hash;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 32400159;
})
cljs.core.Vector.cljs$lang$type = true;
cljs.core.Vector.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/Vector");
});
cljs.core.Vector.prototype.cljs$core$IHash$_hash$arity$1 = (function (coll){
var this__8340 = this;
var h__2220__auto____8341 = this__8340.__hash;
if(!((h__2220__auto____8341 == null)))
{return h__2220__auto____8341;
} else
{var h__2220__auto____8342 = cljs.core.hash_coll.call(null,coll);
this__8340.__hash = h__2220__auto____8342;
return h__2220__auto____8342;
}
});
cljs.core.Vector.prototype.cljs$core$ILookup$_lookup$arity$2 = (function (coll,k){
var this__8343 = this;
return coll.cljs$core$IIndexed$_nth$arity$3(coll,k,null);
});
cljs.core.Vector.prototype.cljs$core$ILookup$_lookup$arity$3 = (function (coll,k,not_found){
var this__8344 = this;
return coll.cljs$core$IIndexed$_nth$arity$3(coll,k,not_found);
});
cljs.core.Vector.prototype.cljs$core$IAssociative$_assoc$arity$3 = (function (coll,k,v){
var this__8345 = this;
var new_array__8346 = this__8345.array.slice();
(new_array__8346[k] = v);
return (new cljs.core.Vector(this__8345.meta,new_array__8346,null));
});
cljs.core.Vector.prototype.call = (function() {
var G__8377 = null;
var G__8377__2 = (function (this_sym8347,k){
var this__8349 = this;
var this_sym8347__8350 = this;
var coll__8351 = this_sym8347__8350;
return coll__8351.cljs$core$ILookup$_lookup$arity$2(coll__8351,k);
});
var G__8377__3 = (function (this_sym8348,k,not_found){
var this__8349 = this;
var this_sym8348__8352 = this;
var coll__8353 = this_sym8348__8352;
return coll__8353.cljs$core$ILookup$_lookup$arity$3(coll__8353,k,not_found);
});
G__8377 = function(this_sym8348,k,not_found){
switch(arguments.length){
case 2:
return G__8377__2.call(this,this_sym8348,k);
case 3:
return G__8377__3.call(this,this_sym8348,k,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
return G__8377;
})()
;
cljs.core.Vector.prototype.apply = (function (this_sym8338,args8339){
var this__8354 = this;
return this_sym8338.call.apply(this_sym8338,[this_sym8338].concat(args8339.slice()));
});
cljs.core.Vector.prototype.cljs$core$ICollection$_conj$arity$2 = (function (coll,o){
var this__8355 = this;
var new_array__8356 = this__8355.array.slice();
new_array__8356.push(o);
return (new cljs.core.Vector(this__8355.meta,new_array__8356,null));
});
cljs.core.Vector.prototype.toString = (function (){
var this__8357 = this;
var this__8358 = this;
return cljs.core.pr_str.call(null,this__8358);
});
cljs.core.Vector.prototype.cljs$core$IReduce$_reduce$arity$2 = (function (v,f){
var this__8359 = this;
return cljs.core.ci_reduce.call(null,this__8359.array,f);
});
cljs.core.Vector.prototype.cljs$core$IReduce$_reduce$arity$3 = (function (v,f,start){
var this__8360 = this;
return cljs.core.ci_reduce.call(null,this__8360.array,f,start);
});
cljs.core.Vector.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (coll){
var this__8361 = this;
if((this__8361.array.length > 0))
{var vector_seq__8362 = (function vector_seq(i){
return (new cljs.core.LazySeq(null,false,(function (){
if((i < this__8361.array.length))
{return cljs.core.cons.call(null,(this__8361.array[i]),vector_seq.call(null,(i + 1)));
} else
{return null;
}
}),null));
});
return vector_seq__8362.call(null,0);
} else
{return null;
}
});
cljs.core.Vector.prototype.cljs$core$ICounted$_count$arity$1 = (function (coll){
var this__8363 = this;
return this__8363.array.length;
});
cljs.core.Vector.prototype.cljs$core$IStack$_peek$arity$1 = (function (coll){
var this__8364 = this;
var count__8365 = this__8364.array.length;
if((count__8365 > 0))
{return (this__8364.array[(count__8365 - 1)]);
} else
{return null;
}
});
cljs.core.Vector.prototype.cljs$core$IStack$_pop$arity$1 = (function (coll){
var this__8366 = this;
if((this__8366.array.length > 0))
{var new_array__8367 = this__8366.array.slice();
new_array__8367.pop();
return (new cljs.core.Vector(this__8366.meta,new_array__8367,null));
} else
{throw (new Error("Can't pop empty vector"));
}
});
cljs.core.Vector.prototype.cljs$core$IVector$_assoc_n$arity$3 = (function (coll,n,val){
var this__8368 = this;
return coll.cljs$core$IAssociative$_assoc$arity$3(coll,n,val);
});
cljs.core.Vector.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (coll,other){
var this__8369 = this;
return cljs.core.equiv_sequential.call(null,coll,other);
});
cljs.core.Vector.prototype.cljs$core$IWithMeta$_with_meta$arity$2 = (function (coll,meta){
var this__8370 = this;
return (new cljs.core.Vector(meta,this__8370.array,this__8370.__hash));
});
cljs.core.Vector.prototype.cljs$core$IMeta$_meta$arity$1 = (function (coll){
var this__8371 = this;
return this__8371.meta;
});
cljs.core.Vector.prototype.cljs$core$IIndexed$_nth$arity$2 = (function (coll,n){
var this__8372 = this;
if((function (){var and__3822__auto____8373 = (0 <= n);
if(and__3822__auto____8373)
{return (n < this__8372.array.length);
} else
{return and__3822__auto____8373;
}
})())
{return (this__8372.array[n]);
} else
{return null;
}
});
cljs.core.Vector.prototype.cljs$core$IIndexed$_nth$arity$3 = (function (coll,n,not_found){
var this__8374 = this;
if((function (){var and__3822__auto____8375 = (0 <= n);
if(and__3822__auto____8375)
{return (n < this__8374.array.length);
} else
{return and__3822__auto____8375;
}
})())
{return (this__8374.array[n]);
} else
{return not_found;
}
});
cljs.core.Vector.prototype.cljs$core$IEmptyableCollection$_empty$arity$1 = (function (coll){
var this__8376 = this;
return cljs.core.with_meta.call(null,cljs.core.Vector.EMPTY,this__8376.meta);
});
cljs.core.Vector;
cljs.core.Vector.EMPTY = (new cljs.core.Vector(null,[],0));
cljs.core.Vector.fromArray = (function (xs){
return (new cljs.core.Vector(null,xs,null));
});

/**
* @constructor
*/
cljs.core.VectorNode = (function (edit,arr){
this.edit = edit;
this.arr = arr;
})
cljs.core.VectorNode.cljs$lang$type = true;
cljs.core.VectorNode.cljs$lang$ctorPrSeq = (function (this__2338__auto__){
return cljs.core.list.call(null,"cljs.core/VectorNode");
});
cljs.core.VectorNode;
cljs.core.pv_fresh_node = (function pv_fresh_node(edit){
return (new cljs.core.VectorNode(edit,cljs.core.make_array.call(null,32)));
});
cljs.core.pv_aget = (function pv_aget(node,idx){
return (node.arr[idx]);
});
cljs.core.pv_aset = (function pv_aset(node,idx,val){
return (node.arr[idx] = val);
});
cljs.core.pv_clone_node = (function pv_clone_node(node){
return (new cljs.core.VectorNode(node.edit,node.arr.slice()));
});
cljs.core.tail_off = (function tail_off(pv){
var cnt__8379 = pv.cnt;
if((cnt__8379 < 32))
{return 0;
} else
{return (((cnt__8379 - 1) >>> 5) << 5);
}
});
cljs.core.new_path = (function new_path(edit,level,node){
var ll__8385 = level;
var ret__8386 = node;
while(true){
if((ll__8385 === 0))
{return ret__8386;
} else
{var embed__8387 = ret__8386;
var r__8388 = cljs.core.pv_fresh_node.call(null,edit);
var ___8389 = cljs.core.pv_aset.call(null,r__8388,0,embed__8387);
{
var G__8390 = (ll__8385 - 5);
var G__8391 = r__8388;
ll__8385 = G__8390;
ret__8386 = G__8391;
continue;
}
}
break;
}
});
cljs.core.push_tail = (function push_tail(pv,level,parent,tailnode){
var ret__8397 = cljs.core.pv_clone_node.call(null,parent);
var subidx__8398 = (((pv.cnt - 1) >>> level) & 31);
if((5 === level))
{cljs.core.pv_aset.call(null,ret__8397,subidx__8398,tailnode);
return ret__8397;
} else
{var child__8399 = cljs.core.pv_aget.call(null,parent,subidx__8398);
if(!((child__8399 == null)))
{var node_to_insert__8400 = push_tail.call(null,pv,(level - 5),child__8399,tailnode);
cljs.core.pv_aset.call(null,ret__8397,subidx__8398,node_to_insert__8400);
return ret__8397;
} else
{var node_to_insert__8401 = cljs.core.new_path.call(null,null,(level - 5),tailnode);
cljs.core.pv_aset.call(null,ret__8397,subidx__8398,node_to_insert__8401);
return ret__8397;
}
}
});
cljs.core.array_for = (function array_for(pv,i){
if((function (){var and__3822__auto____8405 = (0 <= i);
if(and__3822__auto____8405)
{return (i < pv.cnt);
} else
{return and__3822__auto____8405;
}
})())
{if((i >= cljs.core.tail_off.call(null,pv)))
{return pv.tail;
} else
{var node__8406 = pv.root;
var level__8407 = pv.shift;
while(true){
if((level__8407 > 0))
{{
var G__8408 = cljs.core.pv_aget.call(null,node__8406,((i >>> level__8407) & 31));
var G__8409 = (level__8407 - 5);
node__8406 = G__8408;
level__8407 = G__8409;
continue;
}
} else
{return node__8406.arr;
}
break;
}
}
} else
{throw (new Error([cljs.core.str("No item "),cljs.core.str(i),cljs.core.str(" in vector of length "),cljs.core.str(pv.cnt)].join('')));
}
});
cljs.core.do_assoc = (function do_assoc(pv,level,node,i,val){
var ret__8412 = cljs.core.pv_clone_node.call(null,node);
if((level === 0))
{cljs.core.pv_aset.call(null,ret__8412,(i & 31),val);
return ret__8412;
} else
{var subidx__8413 = ((i >>> level) & 31);
cljs.core.pv_aset.call(null,ret__8412,subidx__8413,do_assoc.call(null,pv,(level - 5),cljs.core.pv_aget.call(null,node,subidx__8413),i,val));
return ret__8412;
}
});
cljs.core.pop_tail = (function pop_tail(pv,level,node){
var subidx__8419 = (((pv.cnt - 2) >>> level) & 31);
if((level > 5))
{var new_child__8420 = pop_tail.call(null,pv,(level - 5),cljs.core.pv_aget.call(null,node,subidx__8419));
if((function (){var and__3822__auto____8421 = (new_child__8420 == null);
if(and__3822__auto____8421)
{return (subidx__8419 === 0);
} else
{return and__3822__auto____8421;
}
})())
{return null;
} else
{var ret__8422 = cljs.core.pv_clone_node.call(null,node);
cljs.core.pv_aset.call(null,ret__8422,subidx__8419,new_child__8420);
return ret__8422;
}
} else
{if((subidx__8419 === 0))
{return null;
} else
{if("\uFDD0'else")
{var ret__8423 = cljs.core.pv_clone_node.call(null,node);
cljs.core.pv_aset.call(null,ret__8423,subidx__8419,null);
return ret__8423;
} else
{return null;
}
}
}
});

/**
* @constructor
*/
cljs.core.PersistentVector = (function (meta,cnt,shift,root,tail,__hash){
this.meta = meta;
this.cnt = cnt;
this.shift = shift;
this.root = root;
this.tail = tail;
this.__hash = __hash;
this.cljs$lang$protocol_mask$partition1$ = 1;
this.cljs$lang$protocol_mask$partition0$ = 167668511;
})
cljs.core.PersistentVector.cljs$lang$type = true;
cljs.core.PersistentVector.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/PersistentVector");
});
cljs.core.PersistentVector.prototype.cljs$core$IEditableCollection$_as_transient$arity$1 = (function (coll){
var this__8426 = this;
return (new cljs.core.TransientVector(this__8426.cnt,this__8426.shift,cljs.core.tv_editable_root.call(null,this__8426.root),cljs.core.tv_editable_tail.call(null,this__8426.tail)));
});
cljs.core.PersistentVector.prototype.cljs$core$IHash$_hash$arity$1 = (function (coll){
var this__8427 = this;
var h__2220__auto____8428 = this__8427.__hash;
if(!((h__2220__auto____8428 == null)))
{return h__2220__auto____8428;
} else
{var h__2220__auto____8429 = cljs.core.hash_coll.call(null,coll);
this__8427.__hash = h__2220__auto____8429;
return h__2220__auto____8429;
}
});
cljs.core.PersistentVector.prototype.cljs$core$ILookup$_lookup$arity$2 = (function (coll,k){
var this__8430 = this;
return coll.cljs$core$IIndexed$_nth$arity$3(coll,k,null);
});
cljs.core.PersistentVector.prototype.cljs$core$ILookup$_lookup$arity$3 = (function (coll,k,not_found){
var this__8431 = this;
return coll.cljs$core$IIndexed$_nth$arity$3(coll,k,not_found);
});
cljs.core.PersistentVector.prototype.cljs$core$IAssociative$_assoc$arity$3 = (function (coll,k,v){
var this__8432 = this;
if((function (){var and__3822__auto____8433 = (0 <= k);
if(and__3822__auto____8433)
{return (k < this__8432.cnt);
} else
{return and__3822__auto____8433;
}
})())
{if((cljs.core.tail_off.call(null,coll) <= k))
{var new_tail__8434 = this__8432.tail.slice();
(new_tail__8434[(k & 31)] = v);
return (new cljs.core.PersistentVector(this__8432.meta,this__8432.cnt,this__8432.shift,this__8432.root,new_tail__8434,null));
} else
{return (new cljs.core.PersistentVector(this__8432.meta,this__8432.cnt,this__8432.shift,cljs.core.do_assoc.call(null,coll,this__8432.shift,this__8432.root,k,v),this__8432.tail,null));
}
} else
{if((k === this__8432.cnt))
{return coll.cljs$core$ICollection$_conj$arity$2(coll,v);
} else
{if("\uFDD0'else")
{throw (new Error([cljs.core.str("Index "),cljs.core.str(k),cljs.core.str(" out of bounds  [0,"),cljs.core.str(this__8432.cnt),cljs.core.str("]")].join('')));
} else
{return null;
}
}
}
});
cljs.core.PersistentVector.prototype.call = (function() {
var G__8482 = null;
var G__8482__2 = (function (this_sym8435,k){
var this__8437 = this;
var this_sym8435__8438 = this;
var coll__8439 = this_sym8435__8438;
return coll__8439.cljs$core$ILookup$_lookup$arity$2(coll__8439,k);
});
var G__8482__3 = (function (this_sym8436,k,not_found){
var this__8437 = this;
var this_sym8436__8440 = this;
var coll__8441 = this_sym8436__8440;
return coll__8441.cljs$core$ILookup$_lookup$arity$3(coll__8441,k,not_found);
});
G__8482 = function(this_sym8436,k,not_found){
switch(arguments.length){
case 2:
return G__8482__2.call(this,this_sym8436,k);
case 3:
return G__8482__3.call(this,this_sym8436,k,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
return G__8482;
})()
;
cljs.core.PersistentVector.prototype.apply = (function (this_sym8424,args8425){
var this__8442 = this;
return this_sym8424.call.apply(this_sym8424,[this_sym8424].concat(args8425.slice()));
});
cljs.core.PersistentVector.prototype.cljs$core$IKVReduce$_kv_reduce$arity$3 = (function (v,f,init){
var this__8443 = this;
var step_init__8444 = [0,init];
var i__8445 = 0;
while(true){
if((i__8445 < this__8443.cnt))
{var arr__8446 = cljs.core.array_for.call(null,v,i__8445);
var len__8447 = arr__8446.length;
var init__8451 = (function (){var j__8448 = 0;
var init__8449 = (step_init__8444[1]);
while(true){
if((j__8448 < len__8447))
{var init__8450 = f.call(null,init__8449,(j__8448 + i__8445),(arr__8446[j__8448]));
if(cljs.core.reduced_QMARK_.call(null,init__8450))
{return init__8450;
} else
{{
var G__8483 = (j__8448 + 1);
var G__8484 = init__8450;
j__8448 = G__8483;
init__8449 = G__8484;
continue;
}
}
} else
{(step_init__8444[0] = len__8447);
(step_init__8444[1] = init__8449);
return init__8449;
}
break;
}
})();
if(cljs.core.reduced_QMARK_.call(null,init__8451))
{return cljs.core.deref.call(null,init__8451);
} else
{{
var G__8485 = (i__8445 + (step_init__8444[0]));
i__8445 = G__8485;
continue;
}
}
} else
{return (step_init__8444[1]);
}
break;
}
});
cljs.core.PersistentVector.prototype.cljs$core$ICollection$_conj$arity$2 = (function (coll,o){
var this__8452 = this;
if(((this__8452.cnt - cljs.core.tail_off.call(null,coll)) < 32))
{var new_tail__8453 = this__8452.tail.slice();
new_tail__8453.push(o);
return (new cljs.core.PersistentVector(this__8452.meta,(this__8452.cnt + 1),this__8452.shift,this__8452.root,new_tail__8453,null));
} else
{var root_overflow_QMARK___8454 = ((this__8452.cnt >>> 5) > (1 << this__8452.shift));
var new_shift__8455 = ((root_overflow_QMARK___8454)?(this__8452.shift + 5):this__8452.shift);
var new_root__8457 = ((root_overflow_QMARK___8454)?(function (){var n_r__8456 = cljs.core.pv_fresh_node.call(null,null);
cljs.core.pv_aset.call(null,n_r__8456,0,this__8452.root);
cljs.core.pv_aset.call(null,n_r__8456,1,cljs.core.new_path.call(null,null,this__8452.shift,(new cljs.core.VectorNode(null,this__8452.tail))));
return n_r__8456;
})():cljs.core.push_tail.call(null,coll,this__8452.shift,this__8452.root,(new cljs.core.VectorNode(null,this__8452.tail))));
return (new cljs.core.PersistentVector(this__8452.meta,(this__8452.cnt + 1),new_shift__8455,new_root__8457,[o],null));
}
});
cljs.core.PersistentVector.prototype.cljs$core$IReversible$_rseq$arity$1 = (function (coll){
var this__8458 = this;
if((this__8458.cnt > 0))
{return (new cljs.core.RSeq(coll,(this__8458.cnt - 1),null));
} else
{return cljs.core.List.EMPTY;
}
});
cljs.core.PersistentVector.prototype.cljs$core$IMapEntry$_key$arity$1 = (function (coll){
var this__8459 = this;
return coll.cljs$core$IIndexed$_nth$arity$2(coll,0);
});
cljs.core.PersistentVector.prototype.cljs$core$IMapEntry$_val$arity$1 = (function (coll){
var this__8460 = this;
return coll.cljs$core$IIndexed$_nth$arity$2(coll,1);
});
cljs.core.PersistentVector.prototype.toString = (function (){
var this__8461 = this;
var this__8462 = this;
return cljs.core.pr_str.call(null,this__8462);
});
cljs.core.PersistentVector.prototype.cljs$core$IReduce$_reduce$arity$2 = (function (v,f){
var this__8463 = this;
return cljs.core.ci_reduce.call(null,v,f);
});
cljs.core.PersistentVector.prototype.cljs$core$IReduce$_reduce$arity$3 = (function (v,f,start){
var this__8464 = this;
return cljs.core.ci_reduce.call(null,v,f,start);
});
cljs.core.PersistentVector.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (coll){
var this__8465 = this;
if((this__8465.cnt === 0))
{return null;
} else
{return cljs.core.chunked_seq.call(null,coll,0,0);
}
});
cljs.core.PersistentVector.prototype.cljs$core$ICounted$_count$arity$1 = (function (coll){
var this__8466 = this;
return this__8466.cnt;
});
cljs.core.PersistentVector.prototype.cljs$core$IStack$_peek$arity$1 = (function (coll){
var this__8467 = this;
if((this__8467.cnt > 0))
{return coll.cljs$core$IIndexed$_nth$arity$2(coll,(this__8467.cnt - 1));
} else
{return null;
}
});
cljs.core.PersistentVector.prototype.cljs$core$IStack$_pop$arity$1 = (function (coll){
var this__8468 = this;
if((this__8468.cnt === 0))
{throw (new Error("Can't pop empty vector"));
} else
{if((1 === this__8468.cnt))
{return cljs.core._with_meta.call(null,cljs.core.PersistentVector.EMPTY,this__8468.meta);
} else
{if((1 < (this__8468.cnt - cljs.core.tail_off.call(null,coll))))
{return (new cljs.core.PersistentVector(this__8468.meta,(this__8468.cnt - 1),this__8468.shift,this__8468.root,this__8468.tail.slice(0,-1),null));
} else
{if("\uFDD0'else")
{var new_tail__8469 = cljs.core.array_for.call(null,coll,(this__8468.cnt - 2));
var nr__8470 = cljs.core.pop_tail.call(null,coll,this__8468.shift,this__8468.root);
var new_root__8471 = (((nr__8470 == null))?cljs.core.PersistentVector.EMPTY_NODE:nr__8470);
var cnt_1__8472 = (this__8468.cnt - 1);
if((function (){var and__3822__auto____8473 = (5 < this__8468.shift);
if(and__3822__auto____8473)
{return (cljs.core.pv_aget.call(null,new_root__8471,1) == null);
} else
{return and__3822__auto____8473;
}
})())
{return (new cljs.core.PersistentVector(this__8468.meta,cnt_1__8472,(this__8468.shift - 5),cljs.core.pv_aget.call(null,new_root__8471,0),new_tail__8469,null));
} else
{return (new cljs.core.PersistentVector(this__8468.meta,cnt_1__8472,this__8468.shift,new_root__8471,new_tail__8469,null));
}
} else
{return null;
}
}
}
}
});
cljs.core.PersistentVector.prototype.cljs$core$IVector$_assoc_n$arity$3 = (function (coll,n,val){
var this__8474 = this;
return coll.cljs$core$IAssociative$_assoc$arity$3(coll,n,val);
});
cljs.core.PersistentVector.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (coll,other){
var this__8475 = this;
return cljs.core.equiv_sequential.call(null,coll,other);
});
cljs.core.PersistentVector.prototype.cljs$core$IWithMeta$_with_meta$arity$2 = (function (coll,meta){
var this__8476 = this;
return (new cljs.core.PersistentVector(meta,this__8476.cnt,this__8476.shift,this__8476.root,this__8476.tail,this__8476.__hash));
});
cljs.core.PersistentVector.prototype.cljs$core$IMeta$_meta$arity$1 = (function (coll){
var this__8477 = this;
return this__8477.meta;
});
cljs.core.PersistentVector.prototype.cljs$core$IIndexed$_nth$arity$2 = (function (coll,n){
var this__8478 = this;
return (cljs.core.array_for.call(null,coll,n)[(n & 31)]);
});
cljs.core.PersistentVector.prototype.cljs$core$IIndexed$_nth$arity$3 = (function (coll,n,not_found){
var this__8479 = this;
if((function (){var and__3822__auto____8480 = (0 <= n);
if(and__3822__auto____8480)
{return (n < this__8479.cnt);
} else
{return and__3822__auto____8480;
}
})())
{return coll.cljs$core$IIndexed$_nth$arity$2(coll,n);
} else
{return not_found;
}
});
cljs.core.PersistentVector.prototype.cljs$core$IEmptyableCollection$_empty$arity$1 = (function (coll){
var this__8481 = this;
return cljs.core.with_meta.call(null,cljs.core.PersistentVector.EMPTY,this__8481.meta);
});
cljs.core.PersistentVector;
cljs.core.PersistentVector.EMPTY_NODE = cljs.core.pv_fresh_node.call(null,null);
cljs.core.PersistentVector.EMPTY = (new cljs.core.PersistentVector(null,0,5,cljs.core.PersistentVector.EMPTY_NODE,[],0));
cljs.core.PersistentVector.fromArray = (function (xs,no_clone){
var l__8486 = xs.length;
var xs__8487 = (((no_clone === true))?xs:xs.slice());
if((l__8486 < 32))
{return (new cljs.core.PersistentVector(null,l__8486,5,cljs.core.PersistentVector.EMPTY_NODE,xs__8487,null));
} else
{var node__8488 = xs__8487.slice(0,32);
var v__8489 = (new cljs.core.PersistentVector(null,32,5,cljs.core.PersistentVector.EMPTY_NODE,node__8488,null));
var i__8490 = 32;
var out__8491 = cljs.core._as_transient.call(null,v__8489);
while(true){
if((i__8490 < l__8486))
{{
var G__8492 = (i__8490 + 1);
var G__8493 = cljs.core.conj_BANG_.call(null,out__8491,(xs__8487[i__8490]));
i__8490 = G__8492;
out__8491 = G__8493;
continue;
}
} else
{return cljs.core.persistent_BANG_.call(null,out__8491);
}
break;
}
}
});
cljs.core.vec = (function vec(coll){
return cljs.core._persistent_BANG_.call(null,cljs.core.reduce.call(null,cljs.core._conj_BANG_,cljs.core._as_transient.call(null,cljs.core.PersistentVector.EMPTY),coll));
});
/**
* @param {...*} var_args
*/
cljs.core.vector = (function() { 
var vector__delegate = function (args){
return cljs.core.vec.call(null,args);
};
var vector = function (var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 0),0);
} 
return vector__delegate.call(this, args);
};
vector.cljs$lang$maxFixedArity = 0;
vector.cljs$lang$applyTo = (function (arglist__8494){
var args = cljs.core.seq(arglist__8494);;
return vector__delegate(args);
});
vector.cljs$lang$arity$variadic = vector__delegate;
return vector;
})()
;

/**
* @constructor
*/
cljs.core.ChunkedSeq = (function (vec,node,i,off,meta){
this.vec = vec;
this.node = node;
this.i = i;
this.off = off;
this.meta = meta;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 27525356;
})
cljs.core.ChunkedSeq.cljs$lang$type = true;
cljs.core.ChunkedSeq.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/ChunkedSeq");
});
cljs.core.ChunkedSeq.prototype.cljs$core$INext$_next$arity$1 = (function (coll){
var this__8495 = this;
if(((this__8495.off + 1) < this__8495.node.length))
{var s__8496 = cljs.core.chunked_seq.call(null,this__8495.vec,this__8495.node,this__8495.i,(this__8495.off + 1));
if((s__8496 == null))
{return null;
} else
{return s__8496;
}
} else
{return coll.cljs$core$IChunkedNext$_chunked_next$arity$1(coll);
}
});
cljs.core.ChunkedSeq.prototype.cljs$core$ICollection$_conj$arity$2 = (function (coll,o){
var this__8497 = this;
return cljs.core.cons.call(null,o,coll);
});
cljs.core.ChunkedSeq.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (coll){
var this__8498 = this;
return coll;
});
cljs.core.ChunkedSeq.prototype.cljs$core$ISeq$_first$arity$1 = (function (coll){
var this__8499 = this;
return (this__8499.node[this__8499.off]);
});
cljs.core.ChunkedSeq.prototype.cljs$core$ISeq$_rest$arity$1 = (function (coll){
var this__8500 = this;
if(((this__8500.off + 1) < this__8500.node.length))
{var s__8501 = cljs.core.chunked_seq.call(null,this__8500.vec,this__8500.node,this__8500.i,(this__8500.off + 1));
if((s__8501 == null))
{return cljs.core.List.EMPTY;
} else
{return s__8501;
}
} else
{return coll.cljs$core$IChunkedSeq$_chunked_rest$arity$1(coll);
}
});
cljs.core.ChunkedSeq.prototype.cljs$core$IChunkedNext$ = true;
cljs.core.ChunkedSeq.prototype.cljs$core$IChunkedNext$_chunked_next$arity$1 = (function (coll){
var this__8502 = this;
var l__8503 = this__8502.node.length;
var s__8504 = ((((this__8502.i + l__8503) < cljs.core._count.call(null,this__8502.vec)))?cljs.core.chunked_seq.call(null,this__8502.vec,(this__8502.i + l__8503),0):null);
if((s__8504 == null))
{return null;
} else
{return s__8504;
}
});
cljs.core.ChunkedSeq.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (coll,other){
var this__8505 = this;
return cljs.core.equiv_sequential.call(null,coll,other);
});
cljs.core.ChunkedSeq.prototype.cljs$core$IWithMeta$_with_meta$arity$2 = (function (coll,m){
var this__8506 = this;
return cljs.core.chunked_seq.call(null,this__8506.vec,this__8506.node,this__8506.i,this__8506.off,m);
});
cljs.core.ChunkedSeq.prototype.cljs$core$IWithMeta$_meta$arity$1 = (function (coll){
var this__8507 = this;
return this__8507.meta;
});
cljs.core.ChunkedSeq.prototype.cljs$core$IEmptyableCollection$_empty$arity$1 = (function (coll){
var this__8508 = this;
return cljs.core.with_meta.call(null,cljs.core.PersistentVector.EMPTY,this__8508.meta);
});
cljs.core.ChunkedSeq.prototype.cljs$core$IChunkedSeq$ = true;
cljs.core.ChunkedSeq.prototype.cljs$core$IChunkedSeq$_chunked_first$arity$1 = (function (coll){
var this__8509 = this;
return cljs.core.array_chunk.call(null,this__8509.node,this__8509.off);
});
cljs.core.ChunkedSeq.prototype.cljs$core$IChunkedSeq$_chunked_rest$arity$1 = (function (coll){
var this__8510 = this;
var l__8511 = this__8510.node.length;
var s__8512 = ((((this__8510.i + l__8511) < cljs.core._count.call(null,this__8510.vec)))?cljs.core.chunked_seq.call(null,this__8510.vec,(this__8510.i + l__8511),0):null);
if((s__8512 == null))
{return cljs.core.List.EMPTY;
} else
{return s__8512;
}
});
cljs.core.ChunkedSeq;
cljs.core.chunked_seq = (function() {
var chunked_seq = null;
var chunked_seq__3 = (function (vec,i,off){
return chunked_seq.call(null,vec,cljs.core.array_for.call(null,vec,i),i,off,null);
});
var chunked_seq__4 = (function (vec,node,i,off){
return chunked_seq.call(null,vec,node,i,off,null);
});
var chunked_seq__5 = (function (vec,node,i,off,meta){
return (new cljs.core.ChunkedSeq(vec,node,i,off,meta));
});
chunked_seq = function(vec,node,i,off,meta){
switch(arguments.length){
case 3:
return chunked_seq__3.call(this,vec,node,i);
case 4:
return chunked_seq__4.call(this,vec,node,i,off);
case 5:
return chunked_seq__5.call(this,vec,node,i,off,meta);
}
throw('Invalid arity: ' + arguments.length);
};
chunked_seq.cljs$lang$arity$3 = chunked_seq__3;
chunked_seq.cljs$lang$arity$4 = chunked_seq__4;
chunked_seq.cljs$lang$arity$5 = chunked_seq__5;
return chunked_seq;
})()
;

/**
* @constructor
*/
cljs.core.Subvec = (function (meta,v,start,end,__hash){
this.meta = meta;
this.v = v;
this.start = start;
this.end = end;
this.__hash = __hash;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 32400159;
})
cljs.core.Subvec.cljs$lang$type = true;
cljs.core.Subvec.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/Subvec");
});
cljs.core.Subvec.prototype.cljs$core$IHash$_hash$arity$1 = (function (coll){
var this__8515 = this;
var h__2220__auto____8516 = this__8515.__hash;
if(!((h__2220__auto____8516 == null)))
{return h__2220__auto____8516;
} else
{var h__2220__auto____8517 = cljs.core.hash_coll.call(null,coll);
this__8515.__hash = h__2220__auto____8517;
return h__2220__auto____8517;
}
});
cljs.core.Subvec.prototype.cljs$core$ILookup$_lookup$arity$2 = (function (coll,k){
var this__8518 = this;
return coll.cljs$core$IIndexed$_nth$arity$3(coll,k,null);
});
cljs.core.Subvec.prototype.cljs$core$ILookup$_lookup$arity$3 = (function (coll,k,not_found){
var this__8519 = this;
return coll.cljs$core$IIndexed$_nth$arity$3(coll,k,not_found);
});
cljs.core.Subvec.prototype.cljs$core$IAssociative$_assoc$arity$3 = (function (coll,key,val){
var this__8520 = this;
var v_pos__8521 = (this__8520.start + key);
return (new cljs.core.Subvec(this__8520.meta,cljs.core._assoc.call(null,this__8520.v,v_pos__8521,val),this__8520.start,((this__8520.end > (v_pos__8521 + 1)) ? this__8520.end : (v_pos__8521 + 1)),null));
});
cljs.core.Subvec.prototype.call = (function() {
var G__8547 = null;
var G__8547__2 = (function (this_sym8522,k){
var this__8524 = this;
var this_sym8522__8525 = this;
var coll__8526 = this_sym8522__8525;
return coll__8526.cljs$core$ILookup$_lookup$arity$2(coll__8526,k);
});
var G__8547__3 = (function (this_sym8523,k,not_found){
var this__8524 = this;
var this_sym8523__8527 = this;
var coll__8528 = this_sym8523__8527;
return coll__8528.cljs$core$ILookup$_lookup$arity$3(coll__8528,k,not_found);
});
G__8547 = function(this_sym8523,k,not_found){
switch(arguments.length){
case 2:
return G__8547__2.call(this,this_sym8523,k);
case 3:
return G__8547__3.call(this,this_sym8523,k,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
return G__8547;
})()
;
cljs.core.Subvec.prototype.apply = (function (this_sym8513,args8514){
var this__8529 = this;
return this_sym8513.call.apply(this_sym8513,[this_sym8513].concat(args8514.slice()));
});
cljs.core.Subvec.prototype.cljs$core$ICollection$_conj$arity$2 = (function (coll,o){
var this__8530 = this;
return (new cljs.core.Subvec(this__8530.meta,cljs.core._assoc_n.call(null,this__8530.v,this__8530.end,o),this__8530.start,(this__8530.end + 1),null));
});
cljs.core.Subvec.prototype.toString = (function (){
var this__8531 = this;
var this__8532 = this;
return cljs.core.pr_str.call(null,this__8532);
});
cljs.core.Subvec.prototype.cljs$core$IReduce$_reduce$arity$2 = (function (coll,f){
var this__8533 = this;
return cljs.core.ci_reduce.call(null,coll,f);
});
cljs.core.Subvec.prototype.cljs$core$IReduce$_reduce$arity$3 = (function (coll,f,start){
var this__8534 = this;
return cljs.core.ci_reduce.call(null,coll,f,start);
});
cljs.core.Subvec.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (coll){
var this__8535 = this;
var subvec_seq__8536 = (function subvec_seq(i){
if((i === this__8535.end))
{return null;
} else
{return cljs.core.cons.call(null,cljs.core._nth.call(null,this__8535.v,i),(new cljs.core.LazySeq(null,false,(function (){
return subvec_seq.call(null,(i + 1));
}),null)));
}
});
return subvec_seq__8536.call(null,this__8535.start);
});
cljs.core.Subvec.prototype.cljs$core$ICounted$_count$arity$1 = (function (coll){
var this__8537 = this;
return (this__8537.end - this__8537.start);
});
cljs.core.Subvec.prototype.cljs$core$IStack$_peek$arity$1 = (function (coll){
var this__8538 = this;
return cljs.core._nth.call(null,this__8538.v,(this__8538.end - 1));
});
cljs.core.Subvec.prototype.cljs$core$IStack$_pop$arity$1 = (function (coll){
var this__8539 = this;
if((this__8539.start === this__8539.end))
{throw (new Error("Can't pop empty vector"));
} else
{return (new cljs.core.Subvec(this__8539.meta,this__8539.v,this__8539.start,(this__8539.end - 1),null));
}
});
cljs.core.Subvec.prototype.cljs$core$IVector$_assoc_n$arity$3 = (function (coll,n,val){
var this__8540 = this;
return coll.cljs$core$IAssociative$_assoc$arity$3(coll,n,val);
});
cljs.core.Subvec.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (coll,other){
var this__8541 = this;
return cljs.core.equiv_sequential.call(null,coll,other);
});
cljs.core.Subvec.prototype.cljs$core$IWithMeta$_with_meta$arity$2 = (function (coll,meta){
var this__8542 = this;
return (new cljs.core.Subvec(meta,this__8542.v,this__8542.start,this__8542.end,this__8542.__hash));
});
cljs.core.Subvec.prototype.cljs$core$IMeta$_meta$arity$1 = (function (coll){
var this__8543 = this;
return this__8543.meta;
});
cljs.core.Subvec.prototype.cljs$core$IIndexed$_nth$arity$2 = (function (coll,n){
var this__8544 = this;
return cljs.core._nth.call(null,this__8544.v,(this__8544.start + n));
});
cljs.core.Subvec.prototype.cljs$core$IIndexed$_nth$arity$3 = (function (coll,n,not_found){
var this__8545 = this;
return cljs.core._nth.call(null,this__8545.v,(this__8545.start + n),not_found);
});
cljs.core.Subvec.prototype.cljs$core$IEmptyableCollection$_empty$arity$1 = (function (coll){
var this__8546 = this;
return cljs.core.with_meta.call(null,cljs.core.Vector.EMPTY,this__8546.meta);
});
cljs.core.Subvec;
/**
* Returns a persistent vector of the items in vector from
* start (inclusive) to end (exclusive).  If end is not supplied,
* defaults to (count vector). This operation is O(1) and very fast, as
* the resulting vector shares structure with the original and no
* trimming is done.
*/
cljs.core.subvec = (function() {
var subvec = null;
var subvec__2 = (function (v,start){
return subvec.call(null,v,start,cljs.core.count.call(null,v));
});
var subvec__3 = (function (v,start,end){
return (new cljs.core.Subvec(null,v,start,end,null));
});
subvec = function(v,start,end){
switch(arguments.length){
case 2:
return subvec__2.call(this,v,start);
case 3:
return subvec__3.call(this,v,start,end);
}
throw('Invalid arity: ' + arguments.length);
};
subvec.cljs$lang$arity$2 = subvec__2;
subvec.cljs$lang$arity$3 = subvec__3;
return subvec;
})()
;
cljs.core.tv_ensure_editable = (function tv_ensure_editable(edit,node){
if((edit === node.edit))
{return node;
} else
{return (new cljs.core.VectorNode(edit,node.arr.slice()));
}
});
cljs.core.tv_editable_root = (function tv_editable_root(node){
return (new cljs.core.VectorNode({},node.arr.slice()));
});
cljs.core.tv_editable_tail = (function tv_editable_tail(tl){
var ret__8549 = cljs.core.make_array.call(null,32);
cljs.core.array_copy.call(null,tl,0,ret__8549,0,tl.length);
return ret__8549;
});
cljs.core.tv_push_tail = (function tv_push_tail(tv,level,parent,tail_node){
var ret__8553 = cljs.core.tv_ensure_editable.call(null,tv.root.edit,parent);
var subidx__8554 = (((tv.cnt - 1) >>> level) & 31);
cljs.core.pv_aset.call(null,ret__8553,subidx__8554,(((level === 5))?tail_node:(function (){var child__8555 = cljs.core.pv_aget.call(null,ret__8553,subidx__8554);
if(!((child__8555 == null)))
{return tv_push_tail.call(null,tv,(level - 5),child__8555,tail_node);
} else
{return cljs.core.new_path.call(null,tv.root.edit,(level - 5),tail_node);
}
})()));
return ret__8553;
});
cljs.core.tv_pop_tail = (function tv_pop_tail(tv,level,node){
var node__8560 = cljs.core.tv_ensure_editable.call(null,tv.root.edit,node);
var subidx__8561 = (((tv.cnt - 2) >>> level) & 31);
if((level > 5))
{var new_child__8562 = tv_pop_tail.call(null,tv,(level - 5),cljs.core.pv_aget.call(null,node__8560,subidx__8561));
if((function (){var and__3822__auto____8563 = (new_child__8562 == null);
if(and__3822__auto____8563)
{return (subidx__8561 === 0);
} else
{return and__3822__auto____8563;
}
})())
{return null;
} else
{cljs.core.pv_aset.call(null,node__8560,subidx__8561,new_child__8562);
return node__8560;
}
} else
{if((subidx__8561 === 0))
{return null;
} else
{if("\uFDD0'else")
{cljs.core.pv_aset.call(null,node__8560,subidx__8561,null);
return node__8560;
} else
{return null;
}
}
}
});
cljs.core.editable_array_for = (function editable_array_for(tv,i){
if((function (){var and__3822__auto____8568 = (0 <= i);
if(and__3822__auto____8568)
{return (i < tv.cnt);
} else
{return and__3822__auto____8568;
}
})())
{if((i >= cljs.core.tail_off.call(null,tv)))
{return tv.tail;
} else
{var root__8569 = tv.root;
var node__8570 = root__8569;
var level__8571 = tv.shift;
while(true){
if((level__8571 > 0))
{{
var G__8572 = cljs.core.tv_ensure_editable.call(null,root__8569.edit,cljs.core.pv_aget.call(null,node__8570,((i >>> level__8571) & 31)));
var G__8573 = (level__8571 - 5);
node__8570 = G__8572;
level__8571 = G__8573;
continue;
}
} else
{return node__8570.arr;
}
break;
}
}
} else
{throw (new Error([cljs.core.str("No item "),cljs.core.str(i),cljs.core.str(" in transient vector of length "),cljs.core.str(tv.cnt)].join('')));
}
});

/**
* @constructor
*/
cljs.core.TransientVector = (function (cnt,shift,root,tail){
this.cnt = cnt;
this.shift = shift;
this.root = root;
this.tail = tail;
this.cljs$lang$protocol_mask$partition0$ = 275;
this.cljs$lang$protocol_mask$partition1$ = 22;
})
cljs.core.TransientVector.cljs$lang$type = true;
cljs.core.TransientVector.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/TransientVector");
});
cljs.core.TransientVector.prototype.call = (function() {
var G__8613 = null;
var G__8613__2 = (function (this_sym8576,k){
var this__8578 = this;
var this_sym8576__8579 = this;
var coll__8580 = this_sym8576__8579;
return coll__8580.cljs$core$ILookup$_lookup$arity$2(coll__8580,k);
});
var G__8613__3 = (function (this_sym8577,k,not_found){
var this__8578 = this;
var this_sym8577__8581 = this;
var coll__8582 = this_sym8577__8581;
return coll__8582.cljs$core$ILookup$_lookup$arity$3(coll__8582,k,not_found);
});
G__8613 = function(this_sym8577,k,not_found){
switch(arguments.length){
case 2:
return G__8613__2.call(this,this_sym8577,k);
case 3:
return G__8613__3.call(this,this_sym8577,k,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
return G__8613;
})()
;
cljs.core.TransientVector.prototype.apply = (function (this_sym8574,args8575){
var this__8583 = this;
return this_sym8574.call.apply(this_sym8574,[this_sym8574].concat(args8575.slice()));
});
cljs.core.TransientVector.prototype.cljs$core$ILookup$_lookup$arity$2 = (function (coll,k){
var this__8584 = this;
return coll.cljs$core$IIndexed$_nth$arity$3(coll,k,null);
});
cljs.core.TransientVector.prototype.cljs$core$ILookup$_lookup$arity$3 = (function (coll,k,not_found){
var this__8585 = this;
return coll.cljs$core$IIndexed$_nth$arity$3(coll,k,not_found);
});
cljs.core.TransientVector.prototype.cljs$core$IIndexed$_nth$arity$2 = (function (coll,n){
var this__8586 = this;
if(this__8586.root.edit)
{return (cljs.core.array_for.call(null,coll,n)[(n & 31)]);
} else
{throw (new Error("nth after persistent!"));
}
});
cljs.core.TransientVector.prototype.cljs$core$IIndexed$_nth$arity$3 = (function (coll,n,not_found){
var this__8587 = this;
if((function (){var and__3822__auto____8588 = (0 <= n);
if(and__3822__auto____8588)
{return (n < this__8587.cnt);
} else
{return and__3822__auto____8588;
}
})())
{return coll.cljs$core$IIndexed$_nth$arity$2(coll,n);
} else
{return not_found;
}
});
cljs.core.TransientVector.prototype.cljs$core$ICounted$_count$arity$1 = (function (coll){
var this__8589 = this;
if(this__8589.root.edit)
{return this__8589.cnt;
} else
{throw (new Error("count after persistent!"));
}
});
cljs.core.TransientVector.prototype.cljs$core$ITransientVector$_assoc_n_BANG_$arity$3 = (function (tcoll,n,val){
var this__8590 = this;
if(this__8590.root.edit)
{if((function (){var and__3822__auto____8591 = (0 <= n);
if(and__3822__auto____8591)
{return (n < this__8590.cnt);
} else
{return and__3822__auto____8591;
}
})())
{if((cljs.core.tail_off.call(null,tcoll) <= n))
{(this__8590.tail[(n & 31)] = val);
return tcoll;
} else
{var new_root__8596 = (function go(level,node){
var node__8594 = cljs.core.tv_ensure_editable.call(null,this__8590.root.edit,node);
if((level === 0))
{cljs.core.pv_aset.call(null,node__8594,(n & 31),val);
return node__8594;
} else
{var subidx__8595 = ((n >>> level) & 31);
cljs.core.pv_aset.call(null,node__8594,subidx__8595,go.call(null,(level - 5),cljs.core.pv_aget.call(null,node__8594,subidx__8595)));
return node__8594;
}
}).call(null,this__8590.shift,this__8590.root);
this__8590.root = new_root__8596;
return tcoll;
}
} else
{if((n === this__8590.cnt))
{return tcoll.cljs$core$ITransientCollection$_conj_BANG_$arity$2(tcoll,val);
} else
{if("\uFDD0'else")
{throw (new Error([cljs.core.str("Index "),cljs.core.str(n),cljs.core.str(" out of bounds for TransientVector of length"),cljs.core.str(this__8590.cnt)].join('')));
} else
{return null;
}
}
}
} else
{throw (new Error("assoc! after persistent!"));
}
});
cljs.core.TransientVector.prototype.cljs$core$ITransientVector$_pop_BANG_$arity$1 = (function (tcoll){
var this__8597 = this;
if(this__8597.root.edit)
{if((this__8597.cnt === 0))
{throw (new Error("Can't pop empty vector"));
} else
{if((1 === this__8597.cnt))
{this__8597.cnt = 0;
return tcoll;
} else
{if((((this__8597.cnt - 1) & 31) > 0))
{this__8597.cnt = (this__8597.cnt - 1);
return tcoll;
} else
{if("\uFDD0'else")
{var new_tail__8598 = cljs.core.editable_array_for.call(null,tcoll,(this__8597.cnt - 2));
var new_root__8600 = (function (){var nr__8599 = cljs.core.tv_pop_tail.call(null,tcoll,this__8597.shift,this__8597.root);
if(!((nr__8599 == null)))
{return nr__8599;
} else
{return (new cljs.core.VectorNode(this__8597.root.edit,cljs.core.make_array.call(null,32)));
}
})();
if((function (){var and__3822__auto____8601 = (5 < this__8597.shift);
if(and__3822__auto____8601)
{return (cljs.core.pv_aget.call(null,new_root__8600,1) == null);
} else
{return and__3822__auto____8601;
}
})())
{var new_root__8602 = cljs.core.tv_ensure_editable.call(null,this__8597.root.edit,cljs.core.pv_aget.call(null,new_root__8600,0));
this__8597.root = new_root__8602;
this__8597.shift = (this__8597.shift - 5);
this__8597.cnt = (this__8597.cnt - 1);
this__8597.tail = new_tail__8598;
return tcoll;
} else
{this__8597.root = new_root__8600;
this__8597.cnt = (this__8597.cnt - 1);
this__8597.tail = new_tail__8598;
return tcoll;
}
} else
{return null;
}
}
}
}
} else
{throw (new Error("pop! after persistent!"));
}
});
cljs.core.TransientVector.prototype.cljs$core$ITransientAssociative$_assoc_BANG_$arity$3 = (function (tcoll,key,val){
var this__8603 = this;
return tcoll.cljs$core$ITransientVector$_assoc_n_BANG_$arity$3(tcoll,key,val);
});
cljs.core.TransientVector.prototype.cljs$core$ITransientCollection$_conj_BANG_$arity$2 = (function (tcoll,o){
var this__8604 = this;
if(this__8604.root.edit)
{if(((this__8604.cnt - cljs.core.tail_off.call(null,tcoll)) < 32))
{(this__8604.tail[(this__8604.cnt & 31)] = o);
this__8604.cnt = (this__8604.cnt + 1);
return tcoll;
} else
{var tail_node__8605 = (new cljs.core.VectorNode(this__8604.root.edit,this__8604.tail));
var new_tail__8606 = cljs.core.make_array.call(null,32);
(new_tail__8606[0] = o);
this__8604.tail = new_tail__8606;
if(((this__8604.cnt >>> 5) > (1 << this__8604.shift)))
{var new_root_array__8607 = cljs.core.make_array.call(null,32);
var new_shift__8608 = (this__8604.shift + 5);
(new_root_array__8607[0] = this__8604.root);
(new_root_array__8607[1] = cljs.core.new_path.call(null,this__8604.root.edit,this__8604.shift,tail_node__8605));
this__8604.root = (new cljs.core.VectorNode(this__8604.root.edit,new_root_array__8607));
this__8604.shift = new_shift__8608;
this__8604.cnt = (this__8604.cnt + 1);
return tcoll;
} else
{var new_root__8609 = cljs.core.tv_push_tail.call(null,tcoll,this__8604.shift,this__8604.root,tail_node__8605);
this__8604.root = new_root__8609;
this__8604.cnt = (this__8604.cnt + 1);
return tcoll;
}
}
} else
{throw (new Error("conj! after persistent!"));
}
});
cljs.core.TransientVector.prototype.cljs$core$ITransientCollection$_persistent_BANG_$arity$1 = (function (tcoll){
var this__8610 = this;
if(this__8610.root.edit)
{this__8610.root.edit = null;
var len__8611 = (this__8610.cnt - cljs.core.tail_off.call(null,tcoll));
var trimmed_tail__8612 = cljs.core.make_array.call(null,len__8611);
cljs.core.array_copy.call(null,this__8610.tail,0,trimmed_tail__8612,0,len__8611);
return (new cljs.core.PersistentVector(null,this__8610.cnt,this__8610.shift,this__8610.root,trimmed_tail__8612,null));
} else
{throw (new Error("persistent! called twice"));
}
});
cljs.core.TransientVector;

/**
* @constructor
*/
cljs.core.PersistentQueueSeq = (function (meta,front,rear,__hash){
this.meta = meta;
this.front = front;
this.rear = rear;
this.__hash = __hash;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 31850572;
})
cljs.core.PersistentQueueSeq.cljs$lang$type = true;
cljs.core.PersistentQueueSeq.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/PersistentQueueSeq");
});
cljs.core.PersistentQueueSeq.prototype.cljs$core$IHash$_hash$arity$1 = (function (coll){
var this__8614 = this;
var h__2220__auto____8615 = this__8614.__hash;
if(!((h__2220__auto____8615 == null)))
{return h__2220__auto____8615;
} else
{var h__2220__auto____8616 = cljs.core.hash_coll.call(null,coll);
this__8614.__hash = h__2220__auto____8616;
return h__2220__auto____8616;
}
});
cljs.core.PersistentQueueSeq.prototype.cljs$core$ICollection$_conj$arity$2 = (function (coll,o){
var this__8617 = this;
return cljs.core.cons.call(null,o,coll);
});
cljs.core.PersistentQueueSeq.prototype.toString = (function (){
var this__8618 = this;
var this__8619 = this;
return cljs.core.pr_str.call(null,this__8619);
});
cljs.core.PersistentQueueSeq.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (coll){
var this__8620 = this;
return coll;
});
cljs.core.PersistentQueueSeq.prototype.cljs$core$ISeq$_first$arity$1 = (function (coll){
var this__8621 = this;
return cljs.core._first.call(null,this__8621.front);
});
cljs.core.PersistentQueueSeq.prototype.cljs$core$ISeq$_rest$arity$1 = (function (coll){
var this__8622 = this;
var temp__3971__auto____8623 = cljs.core.next.call(null,this__8622.front);
if(temp__3971__auto____8623)
{var f1__8624 = temp__3971__auto____8623;
return (new cljs.core.PersistentQueueSeq(this__8622.meta,f1__8624,this__8622.rear,null));
} else
{if((this__8622.rear == null))
{return coll.cljs$core$IEmptyableCollection$_empty$arity$1(coll);
} else
{return (new cljs.core.PersistentQueueSeq(this__8622.meta,this__8622.rear,null,null));
}
}
});
cljs.core.PersistentQueueSeq.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (coll,other){
var this__8625 = this;
return cljs.core.equiv_sequential.call(null,coll,other);
});
cljs.core.PersistentQueueSeq.prototype.cljs$core$IWithMeta$_with_meta$arity$2 = (function (coll,meta){
var this__8626 = this;
return (new cljs.core.PersistentQueueSeq(meta,this__8626.front,this__8626.rear,this__8626.__hash));
});
cljs.core.PersistentQueueSeq.prototype.cljs$core$IMeta$_meta$arity$1 = (function (coll){
var this__8627 = this;
return this__8627.meta;
});
cljs.core.PersistentQueueSeq.prototype.cljs$core$IEmptyableCollection$_empty$arity$1 = (function (coll){
var this__8628 = this;
return cljs.core.with_meta.call(null,cljs.core.List.EMPTY,this__8628.meta);
});
cljs.core.PersistentQueueSeq;

/**
* @constructor
*/
cljs.core.PersistentQueue = (function (meta,count,front,rear,__hash){
this.meta = meta;
this.count = count;
this.front = front;
this.rear = rear;
this.__hash = __hash;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 31858766;
})
cljs.core.PersistentQueue.cljs$lang$type = true;
cljs.core.PersistentQueue.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/PersistentQueue");
});
cljs.core.PersistentQueue.prototype.cljs$core$IHash$_hash$arity$1 = (function (coll){
var this__8629 = this;
var h__2220__auto____8630 = this__8629.__hash;
if(!((h__2220__auto____8630 == null)))
{return h__2220__auto____8630;
} else
{var h__2220__auto____8631 = cljs.core.hash_coll.call(null,coll);
this__8629.__hash = h__2220__auto____8631;
return h__2220__auto____8631;
}
});
cljs.core.PersistentQueue.prototype.cljs$core$ICollection$_conj$arity$2 = (function (coll,o){
var this__8632 = this;
if(cljs.core.truth_(this__8632.front))
{return (new cljs.core.PersistentQueue(this__8632.meta,(this__8632.count + 1),this__8632.front,cljs.core.conj.call(null,(function (){var or__3824__auto____8633 = this__8632.rear;
if(cljs.core.truth_(or__3824__auto____8633))
{return or__3824__auto____8633;
} else
{return cljs.core.PersistentVector.EMPTY;
}
})(),o),null));
} else
{return (new cljs.core.PersistentQueue(this__8632.meta,(this__8632.count + 1),cljs.core.conj.call(null,this__8632.front,o),cljs.core.PersistentVector.EMPTY,null));
}
});
cljs.core.PersistentQueue.prototype.toString = (function (){
var this__8634 = this;
var this__8635 = this;
return cljs.core.pr_str.call(null,this__8635);
});
cljs.core.PersistentQueue.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (coll){
var this__8636 = this;
var rear__8637 = cljs.core.seq.call(null,this__8636.rear);
if(cljs.core.truth_((function (){var or__3824__auto____8638 = this__8636.front;
if(cljs.core.truth_(or__3824__auto____8638))
{return or__3824__auto____8638;
} else
{return rear__8637;
}
})()))
{return (new cljs.core.PersistentQueueSeq(null,this__8636.front,cljs.core.seq.call(null,rear__8637),null));
} else
{return null;
}
});
cljs.core.PersistentQueue.prototype.cljs$core$ICounted$_count$arity$1 = (function (coll){
var this__8639 = this;
return this__8639.count;
});
cljs.core.PersistentQueue.prototype.cljs$core$IStack$_peek$arity$1 = (function (coll){
var this__8640 = this;
return cljs.core._first.call(null,this__8640.front);
});
cljs.core.PersistentQueue.prototype.cljs$core$IStack$_pop$arity$1 = (function (coll){
var this__8641 = this;
if(cljs.core.truth_(this__8641.front))
{var temp__3971__auto____8642 = cljs.core.next.call(null,this__8641.front);
if(temp__3971__auto____8642)
{var f1__8643 = temp__3971__auto____8642;
return (new cljs.core.PersistentQueue(this__8641.meta,(this__8641.count - 1),f1__8643,this__8641.rear,null));
} else
{return (new cljs.core.PersistentQueue(this__8641.meta,(this__8641.count - 1),cljs.core.seq.call(null,this__8641.rear),cljs.core.PersistentVector.EMPTY,null));
}
} else
{return coll;
}
});
cljs.core.PersistentQueue.prototype.cljs$core$ISeq$_first$arity$1 = (function (coll){
var this__8644 = this;
return cljs.core.first.call(null,this__8644.front);
});
cljs.core.PersistentQueue.prototype.cljs$core$ISeq$_rest$arity$1 = (function (coll){
var this__8645 = this;
return cljs.core.rest.call(null,cljs.core.seq.call(null,coll));
});
cljs.core.PersistentQueue.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (coll,other){
var this__8646 = this;
return cljs.core.equiv_sequential.call(null,coll,other);
});
cljs.core.PersistentQueue.prototype.cljs$core$IWithMeta$_with_meta$arity$2 = (function (coll,meta){
var this__8647 = this;
return (new cljs.core.PersistentQueue(meta,this__8647.count,this__8647.front,this__8647.rear,this__8647.__hash));
});
cljs.core.PersistentQueue.prototype.cljs$core$IMeta$_meta$arity$1 = (function (coll){
var this__8648 = this;
return this__8648.meta;
});
cljs.core.PersistentQueue.prototype.cljs$core$IEmptyableCollection$_empty$arity$1 = (function (coll){
var this__8649 = this;
return cljs.core.PersistentQueue.EMPTY;
});
cljs.core.PersistentQueue;
cljs.core.PersistentQueue.EMPTY = (new cljs.core.PersistentQueue(null,0,null,cljs.core.PersistentVector.EMPTY,0));

/**
* @constructor
*/
cljs.core.NeverEquiv = (function (){
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 2097152;
})
cljs.core.NeverEquiv.cljs$lang$type = true;
cljs.core.NeverEquiv.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/NeverEquiv");
});
cljs.core.NeverEquiv.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (o,other){
var this__8650 = this;
return false;
});
cljs.core.NeverEquiv;
cljs.core.never_equiv = (new cljs.core.NeverEquiv());
/**
* Assumes y is a map. Returns true if x equals y, otherwise returns
* false.
*/
cljs.core.equiv_map = (function equiv_map(x,y){
return cljs.core.boolean$.call(null,((cljs.core.map_QMARK_.call(null,y))?(((cljs.core.count.call(null,x) === cljs.core.count.call(null,y)))?cljs.core.every_QMARK_.call(null,cljs.core.identity,cljs.core.map.call(null,(function (xkv){
return cljs.core._EQ_.call(null,cljs.core._lookup.call(null,y,cljs.core.first.call(null,xkv),cljs.core.never_equiv),cljs.core.second.call(null,xkv));
}),x)):null):null));
});
cljs.core.scan_array = (function scan_array(incr,k,array){
var len__8653 = array.length;
var i__8654 = 0;
while(true){
if((i__8654 < len__8653))
{if((k === (array[i__8654])))
{return i__8654;
} else
{{
var G__8655 = (i__8654 + incr);
i__8654 = G__8655;
continue;
}
}
} else
{return null;
}
break;
}
});
cljs.core.obj_map_compare_keys = (function obj_map_compare_keys(a,b){
var a__8658 = cljs.core.hash.call(null,a);
var b__8659 = cljs.core.hash.call(null,b);
if((a__8658 < b__8659))
{return -1;
} else
{if((a__8658 > b__8659))
{return 1;
} else
{if("\uFDD0'else")
{return 0;
} else
{return null;
}
}
}
});
cljs.core.obj_map__GT_hash_map = (function obj_map__GT_hash_map(m,k,v){
var ks__8667 = m.keys;
var len__8668 = ks__8667.length;
var so__8669 = m.strobj;
var out__8670 = cljs.core.with_meta.call(null,cljs.core.PersistentHashMap.EMPTY,cljs.core.meta.call(null,m));
var i__8671 = 0;
var out__8672 = cljs.core.transient$.call(null,out__8670);
while(true){
if((i__8671 < len__8668))
{var k__8673 = (ks__8667[i__8671]);
{
var G__8674 = (i__8671 + 1);
var G__8675 = cljs.core.assoc_BANG_.call(null,out__8672,k__8673,(so__8669[k__8673]));
i__8671 = G__8674;
out__8672 = G__8675;
continue;
}
} else
{return cljs.core.persistent_BANG_.call(null,cljs.core.assoc_BANG_.call(null,out__8672,k,v));
}
break;
}
});
cljs.core.obj_clone = (function obj_clone(obj,ks){
var new_obj__8681 = {};
var l__8682 = ks.length;
var i__8683 = 0;
while(true){
if((i__8683 < l__8682))
{var k__8684 = (ks[i__8683]);
(new_obj__8681[k__8684] = (obj[k__8684]));
{
var G__8685 = (i__8683 + 1);
i__8683 = G__8685;
continue;
}
} else
{}
break;
}
return new_obj__8681;
});

/**
* @constructor
*/
cljs.core.ObjMap = (function (meta,keys,strobj,update_count,__hash){
this.meta = meta;
this.keys = keys;
this.strobj = strobj;
this.update_count = update_count;
this.__hash = __hash;
this.cljs$lang$protocol_mask$partition1$ = 1;
this.cljs$lang$protocol_mask$partition0$ = 15075087;
})
cljs.core.ObjMap.cljs$lang$type = true;
cljs.core.ObjMap.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/ObjMap");
});
cljs.core.ObjMap.prototype.cljs$core$IEditableCollection$_as_transient$arity$1 = (function (coll){
var this__8688 = this;
return cljs.core.transient$.call(null,cljs.core.into.call(null,cljs.core.hash_map.call(null),coll));
});
cljs.core.ObjMap.prototype.cljs$core$IHash$_hash$arity$1 = (function (coll){
var this__8689 = this;
var h__2220__auto____8690 = this__8689.__hash;
if(!((h__2220__auto____8690 == null)))
{return h__2220__auto____8690;
} else
{var h__2220__auto____8691 = cljs.core.hash_imap.call(null,coll);
this__8689.__hash = h__2220__auto____8691;
return h__2220__auto____8691;
}
});
cljs.core.ObjMap.prototype.cljs$core$ILookup$_lookup$arity$2 = (function (coll,k){
var this__8692 = this;
return coll.cljs$core$ILookup$_lookup$arity$3(coll,k,null);
});
cljs.core.ObjMap.prototype.cljs$core$ILookup$_lookup$arity$3 = (function (coll,k,not_found){
var this__8693 = this;
if((function (){var and__3822__auto____8694 = goog.isString(k);
if(and__3822__auto____8694)
{return !((cljs.core.scan_array.call(null,1,k,this__8693.keys) == null));
} else
{return and__3822__auto____8694;
}
})())
{return (this__8693.strobj[k]);
} else
{return not_found;
}
});
cljs.core.ObjMap.prototype.cljs$core$IAssociative$_assoc$arity$3 = (function (coll,k,v){
var this__8695 = this;
if(goog.isString(k))
{if((function (){var or__3824__auto____8696 = (this__8695.update_count > cljs.core.ObjMap.HASHMAP_THRESHOLD);
if(or__3824__auto____8696)
{return or__3824__auto____8696;
} else
{return (this__8695.keys.length >= cljs.core.ObjMap.HASHMAP_THRESHOLD);
}
})())
{return cljs.core.obj_map__GT_hash_map.call(null,coll,k,v);
} else
{if(!((cljs.core.scan_array.call(null,1,k,this__8695.keys) == null)))
{var new_strobj__8697 = cljs.core.obj_clone.call(null,this__8695.strobj,this__8695.keys);
(new_strobj__8697[k] = v);
return (new cljs.core.ObjMap(this__8695.meta,this__8695.keys,new_strobj__8697,(this__8695.update_count + 1),null));
} else
{var new_strobj__8698 = cljs.core.obj_clone.call(null,this__8695.strobj,this__8695.keys);
var new_keys__8699 = this__8695.keys.slice();
(new_strobj__8698[k] = v);
new_keys__8699.push(k);
return (new cljs.core.ObjMap(this__8695.meta,new_keys__8699,new_strobj__8698,(this__8695.update_count + 1),null));
}
}
} else
{return cljs.core.obj_map__GT_hash_map.call(null,coll,k,v);
}
});
cljs.core.ObjMap.prototype.cljs$core$IAssociative$_contains_key_QMARK_$arity$2 = (function (coll,k){
var this__8700 = this;
if((function (){var and__3822__auto____8701 = goog.isString(k);
if(and__3822__auto____8701)
{return !((cljs.core.scan_array.call(null,1,k,this__8700.keys) == null));
} else
{return and__3822__auto____8701;
}
})())
{return true;
} else
{return false;
}
});
cljs.core.ObjMap.prototype.call = (function() {
var G__8723 = null;
var G__8723__2 = (function (this_sym8702,k){
var this__8704 = this;
var this_sym8702__8705 = this;
var coll__8706 = this_sym8702__8705;
return coll__8706.cljs$core$ILookup$_lookup$arity$2(coll__8706,k);
});
var G__8723__3 = (function (this_sym8703,k,not_found){
var this__8704 = this;
var this_sym8703__8707 = this;
var coll__8708 = this_sym8703__8707;
return coll__8708.cljs$core$ILookup$_lookup$arity$3(coll__8708,k,not_found);
});
G__8723 = function(this_sym8703,k,not_found){
switch(arguments.length){
case 2:
return G__8723__2.call(this,this_sym8703,k);
case 3:
return G__8723__3.call(this,this_sym8703,k,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
return G__8723;
})()
;
cljs.core.ObjMap.prototype.apply = (function (this_sym8686,args8687){
var this__8709 = this;
return this_sym8686.call.apply(this_sym8686,[this_sym8686].concat(args8687.slice()));
});
cljs.core.ObjMap.prototype.cljs$core$ICollection$_conj$arity$2 = (function (coll,entry){
var this__8710 = this;
if(cljs.core.vector_QMARK_.call(null,entry))
{return coll.cljs$core$IAssociative$_assoc$arity$3(coll,cljs.core._nth.call(null,entry,0),cljs.core._nth.call(null,entry,1));
} else
{return cljs.core.reduce.call(null,cljs.core._conj,coll,entry);
}
});
cljs.core.ObjMap.prototype.toString = (function (){
var this__8711 = this;
var this__8712 = this;
return cljs.core.pr_str.call(null,this__8712);
});
cljs.core.ObjMap.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (coll){
var this__8713 = this;
if((this__8713.keys.length > 0))
{return cljs.core.map.call(null,(function (p1__8676_SHARP_){
return cljs.core.vector.call(null,p1__8676_SHARP_,(this__8713.strobj[p1__8676_SHARP_]));
}),this__8713.keys.sort(cljs.core.obj_map_compare_keys));
} else
{return null;
}
});
cljs.core.ObjMap.prototype.cljs$core$ICounted$_count$arity$1 = (function (coll){
var this__8714 = this;
return this__8714.keys.length;
});
cljs.core.ObjMap.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (coll,other){
var this__8715 = this;
return cljs.core.equiv_map.call(null,coll,other);
});
cljs.core.ObjMap.prototype.cljs$core$IWithMeta$_with_meta$arity$2 = (function (coll,meta){
var this__8716 = this;
return (new cljs.core.ObjMap(meta,this__8716.keys,this__8716.strobj,this__8716.update_count,this__8716.__hash));
});
cljs.core.ObjMap.prototype.cljs$core$IMeta$_meta$arity$1 = (function (coll){
var this__8717 = this;
return this__8717.meta;
});
cljs.core.ObjMap.prototype.cljs$core$IEmptyableCollection$_empty$arity$1 = (function (coll){
var this__8718 = this;
return cljs.core.with_meta.call(null,cljs.core.ObjMap.EMPTY,this__8718.meta);
});
cljs.core.ObjMap.prototype.cljs$core$IMap$_dissoc$arity$2 = (function (coll,k){
var this__8719 = this;
if((function (){var and__3822__auto____8720 = goog.isString(k);
if(and__3822__auto____8720)
{return !((cljs.core.scan_array.call(null,1,k,this__8719.keys) == null));
} else
{return and__3822__auto____8720;
}
})())
{var new_keys__8721 = this__8719.keys.slice();
var new_strobj__8722 = cljs.core.obj_clone.call(null,this__8719.strobj,this__8719.keys);
new_keys__8721.splice(cljs.core.scan_array.call(null,1,k,new_keys__8721),1);
cljs.core.js_delete.call(null,new_strobj__8722,k);
return (new cljs.core.ObjMap(this__8719.meta,new_keys__8721,new_strobj__8722,(this__8719.update_count + 1),null));
} else
{return coll;
}
});
cljs.core.ObjMap;
cljs.core.ObjMap.EMPTY = (new cljs.core.ObjMap(null,[],{},0,0));
cljs.core.ObjMap.HASHMAP_THRESHOLD = 32;
cljs.core.ObjMap.fromObject = (function (ks,obj){
return (new cljs.core.ObjMap(null,ks,obj,0,null));
});

/**
* @constructor
*/
cljs.core.HashMap = (function (meta,count,hashobj,__hash){
this.meta = meta;
this.count = count;
this.hashobj = hashobj;
this.__hash = __hash;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 15075087;
})
cljs.core.HashMap.cljs$lang$type = true;
cljs.core.HashMap.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/HashMap");
});
cljs.core.HashMap.prototype.cljs$core$IHash$_hash$arity$1 = (function (coll){
var this__8727 = this;
var h__2220__auto____8728 = this__8727.__hash;
if(!((h__2220__auto____8728 == null)))
{return h__2220__auto____8728;
} else
{var h__2220__auto____8729 = cljs.core.hash_imap.call(null,coll);
this__8727.__hash = h__2220__auto____8729;
return h__2220__auto____8729;
}
});
cljs.core.HashMap.prototype.cljs$core$ILookup$_lookup$arity$2 = (function (coll,k){
var this__8730 = this;
return coll.cljs$core$ILookup$_lookup$arity$3(coll,k,null);
});
cljs.core.HashMap.prototype.cljs$core$ILookup$_lookup$arity$3 = (function (coll,k,not_found){
var this__8731 = this;
var bucket__8732 = (this__8731.hashobj[cljs.core.hash.call(null,k)]);
var i__8733 = (cljs.core.truth_(bucket__8732)?cljs.core.scan_array.call(null,2,k,bucket__8732):null);
if(cljs.core.truth_(i__8733))
{return (bucket__8732[(i__8733 + 1)]);
} else
{return not_found;
}
});
cljs.core.HashMap.prototype.cljs$core$IAssociative$_assoc$arity$3 = (function (coll,k,v){
var this__8734 = this;
var h__8735 = cljs.core.hash.call(null,k);
var bucket__8736 = (this__8734.hashobj[h__8735]);
if(cljs.core.truth_(bucket__8736))
{var new_bucket__8737 = bucket__8736.slice();
var new_hashobj__8738 = goog.object.clone(this__8734.hashobj);
(new_hashobj__8738[h__8735] = new_bucket__8737);
var temp__3971__auto____8739 = cljs.core.scan_array.call(null,2,k,new_bucket__8737);
if(cljs.core.truth_(temp__3971__auto____8739))
{var i__8740 = temp__3971__auto____8739;
(new_bucket__8737[(i__8740 + 1)] = v);
return (new cljs.core.HashMap(this__8734.meta,this__8734.count,new_hashobj__8738,null));
} else
{new_bucket__8737.push(k,v);
return (new cljs.core.HashMap(this__8734.meta,(this__8734.count + 1),new_hashobj__8738,null));
}
} else
{var new_hashobj__8741 = goog.object.clone(this__8734.hashobj);
(new_hashobj__8741[h__8735] = [k,v]);
return (new cljs.core.HashMap(this__8734.meta,(this__8734.count + 1),new_hashobj__8741,null));
}
});
cljs.core.HashMap.prototype.cljs$core$IAssociative$_contains_key_QMARK_$arity$2 = (function (coll,k){
var this__8742 = this;
var bucket__8743 = (this__8742.hashobj[cljs.core.hash.call(null,k)]);
var i__8744 = (cljs.core.truth_(bucket__8743)?cljs.core.scan_array.call(null,2,k,bucket__8743):null);
if(cljs.core.truth_(i__8744))
{return true;
} else
{return false;
}
});
cljs.core.HashMap.prototype.call = (function() {
var G__8769 = null;
var G__8769__2 = (function (this_sym8745,k){
var this__8747 = this;
var this_sym8745__8748 = this;
var coll__8749 = this_sym8745__8748;
return coll__8749.cljs$core$ILookup$_lookup$arity$2(coll__8749,k);
});
var G__8769__3 = (function (this_sym8746,k,not_found){
var this__8747 = this;
var this_sym8746__8750 = this;
var coll__8751 = this_sym8746__8750;
return coll__8751.cljs$core$ILookup$_lookup$arity$3(coll__8751,k,not_found);
});
G__8769 = function(this_sym8746,k,not_found){
switch(arguments.length){
case 2:
return G__8769__2.call(this,this_sym8746,k);
case 3:
return G__8769__3.call(this,this_sym8746,k,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
return G__8769;
})()
;
cljs.core.HashMap.prototype.apply = (function (this_sym8725,args8726){
var this__8752 = this;
return this_sym8725.call.apply(this_sym8725,[this_sym8725].concat(args8726.slice()));
});
cljs.core.HashMap.prototype.cljs$core$ICollection$_conj$arity$2 = (function (coll,entry){
var this__8753 = this;
if(cljs.core.vector_QMARK_.call(null,entry))
{return coll.cljs$core$IAssociative$_assoc$arity$3(coll,cljs.core._nth.call(null,entry,0),cljs.core._nth.call(null,entry,1));
} else
{return cljs.core.reduce.call(null,cljs.core._conj,coll,entry);
}
});
cljs.core.HashMap.prototype.toString = (function (){
var this__8754 = this;
var this__8755 = this;
return cljs.core.pr_str.call(null,this__8755);
});
cljs.core.HashMap.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (coll){
var this__8756 = this;
if((this__8756.count > 0))
{var hashes__8757 = cljs.core.js_keys.call(null,this__8756.hashobj).sort();
return cljs.core.mapcat.call(null,(function (p1__8724_SHARP_){
return cljs.core.map.call(null,cljs.core.vec,cljs.core.partition.call(null,2,(this__8756.hashobj[p1__8724_SHARP_])));
}),hashes__8757);
} else
{return null;
}
});
cljs.core.HashMap.prototype.cljs$core$ICounted$_count$arity$1 = (function (coll){
var this__8758 = this;
return this__8758.count;
});
cljs.core.HashMap.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (coll,other){
var this__8759 = this;
return cljs.core.equiv_map.call(null,coll,other);
});
cljs.core.HashMap.prototype.cljs$core$IWithMeta$_with_meta$arity$2 = (function (coll,meta){
var this__8760 = this;
return (new cljs.core.HashMap(meta,this__8760.count,this__8760.hashobj,this__8760.__hash));
});
cljs.core.HashMap.prototype.cljs$core$IMeta$_meta$arity$1 = (function (coll){
var this__8761 = this;
return this__8761.meta;
});
cljs.core.HashMap.prototype.cljs$core$IEmptyableCollection$_empty$arity$1 = (function (coll){
var this__8762 = this;
return cljs.core.with_meta.call(null,cljs.core.HashMap.EMPTY,this__8762.meta);
});
cljs.core.HashMap.prototype.cljs$core$IMap$_dissoc$arity$2 = (function (coll,k){
var this__8763 = this;
var h__8764 = cljs.core.hash.call(null,k);
var bucket__8765 = (this__8763.hashobj[h__8764]);
var i__8766 = (cljs.core.truth_(bucket__8765)?cljs.core.scan_array.call(null,2,k,bucket__8765):null);
if(cljs.core.not.call(null,i__8766))
{return coll;
} else
{var new_hashobj__8767 = goog.object.clone(this__8763.hashobj);
if((3 > bucket__8765.length))
{cljs.core.js_delete.call(null,new_hashobj__8767,h__8764);
} else
{var new_bucket__8768 = bucket__8765.slice();
new_bucket__8768.splice(i__8766,2);
(new_hashobj__8767[h__8764] = new_bucket__8768);
}
return (new cljs.core.HashMap(this__8763.meta,(this__8763.count - 1),new_hashobj__8767,null));
}
});
cljs.core.HashMap;
cljs.core.HashMap.EMPTY = (new cljs.core.HashMap(null,0,{},0));
cljs.core.HashMap.fromArrays = (function (ks,vs){
var len__8770 = ks.length;
var i__8771 = 0;
var out__8772 = cljs.core.HashMap.EMPTY;
while(true){
if((i__8771 < len__8770))
{{
var G__8773 = (i__8771 + 1);
var G__8774 = cljs.core.assoc.call(null,out__8772,(ks[i__8771]),(vs[i__8771]));
i__8771 = G__8773;
out__8772 = G__8774;
continue;
}
} else
{return out__8772;
}
break;
}
});
cljs.core.array_map_index_of = (function array_map_index_of(m,k){
var arr__8778 = m.arr;
var len__8779 = arr__8778.length;
var i__8780 = 0;
while(true){
if((len__8779 <= i__8780))
{return -1;
} else
{if(cljs.core._EQ_.call(null,(arr__8778[i__8780]),k))
{return i__8780;
} else
{if("\uFDD0'else")
{{
var G__8781 = (i__8780 + 2);
i__8780 = G__8781;
continue;
}
} else
{return null;
}
}
}
break;
}
});

/**
* @constructor
*/
cljs.core.PersistentArrayMap = (function (meta,cnt,arr,__hash){
this.meta = meta;
this.cnt = cnt;
this.arr = arr;
this.__hash = __hash;
this.cljs$lang$protocol_mask$partition1$ = 1;
this.cljs$lang$protocol_mask$partition0$ = 16123663;
})
cljs.core.PersistentArrayMap.cljs$lang$type = true;
cljs.core.PersistentArrayMap.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/PersistentArrayMap");
});
cljs.core.PersistentArrayMap.prototype.cljs$core$IEditableCollection$_as_transient$arity$1 = (function (coll){
var this__8784 = this;
return (new cljs.core.TransientArrayMap({},this__8784.arr.length,this__8784.arr.slice()));
});
cljs.core.PersistentArrayMap.prototype.cljs$core$IHash$_hash$arity$1 = (function (coll){
var this__8785 = this;
var h__2220__auto____8786 = this__8785.__hash;
if(!((h__2220__auto____8786 == null)))
{return h__2220__auto____8786;
} else
{var h__2220__auto____8787 = cljs.core.hash_imap.call(null,coll);
this__8785.__hash = h__2220__auto____8787;
return h__2220__auto____8787;
}
});
cljs.core.PersistentArrayMap.prototype.cljs$core$ILookup$_lookup$arity$2 = (function (coll,k){
var this__8788 = this;
return coll.cljs$core$ILookup$_lookup$arity$3(coll,k,null);
});
cljs.core.PersistentArrayMap.prototype.cljs$core$ILookup$_lookup$arity$3 = (function (coll,k,not_found){
var this__8789 = this;
var idx__8790 = cljs.core.array_map_index_of.call(null,coll,k);
if((idx__8790 === -1))
{return not_found;
} else
{return (this__8789.arr[(idx__8790 + 1)]);
}
});
cljs.core.PersistentArrayMap.prototype.cljs$core$IAssociative$_assoc$arity$3 = (function (coll,k,v){
var this__8791 = this;
var idx__8792 = cljs.core.array_map_index_of.call(null,coll,k);
if((idx__8792 === -1))
{if((this__8791.cnt < cljs.core.PersistentArrayMap.HASHMAP_THRESHOLD))
{return (new cljs.core.PersistentArrayMap(this__8791.meta,(this__8791.cnt + 1),(function (){var G__8793__8794 = this__8791.arr.slice();
G__8793__8794.push(k);
G__8793__8794.push(v);
return G__8793__8794;
})(),null));
} else
{return cljs.core.persistent_BANG_.call(null,cljs.core.assoc_BANG_.call(null,cljs.core.transient$.call(null,cljs.core.into.call(null,cljs.core.PersistentHashMap.EMPTY,coll)),k,v));
}
} else
{if((v === (this__8791.arr[(idx__8792 + 1)])))
{return coll;
} else
{if("\uFDD0'else")
{return (new cljs.core.PersistentArrayMap(this__8791.meta,this__8791.cnt,(function (){var G__8795__8796 = this__8791.arr.slice();
(G__8795__8796[(idx__8792 + 1)] = v);
return G__8795__8796;
})(),null));
} else
{return null;
}
}
}
});
cljs.core.PersistentArrayMap.prototype.cljs$core$IAssociative$_contains_key_QMARK_$arity$2 = (function (coll,k){
var this__8797 = this;
return !((cljs.core.array_map_index_of.call(null,coll,k) === -1));
});
cljs.core.PersistentArrayMap.prototype.call = (function() {
var G__8829 = null;
var G__8829__2 = (function (this_sym8798,k){
var this__8800 = this;
var this_sym8798__8801 = this;
var coll__8802 = this_sym8798__8801;
return coll__8802.cljs$core$ILookup$_lookup$arity$2(coll__8802,k);
});
var G__8829__3 = (function (this_sym8799,k,not_found){
var this__8800 = this;
var this_sym8799__8803 = this;
var coll__8804 = this_sym8799__8803;
return coll__8804.cljs$core$ILookup$_lookup$arity$3(coll__8804,k,not_found);
});
G__8829 = function(this_sym8799,k,not_found){
switch(arguments.length){
case 2:
return G__8829__2.call(this,this_sym8799,k);
case 3:
return G__8829__3.call(this,this_sym8799,k,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
return G__8829;
})()
;
cljs.core.PersistentArrayMap.prototype.apply = (function (this_sym8782,args8783){
var this__8805 = this;
return this_sym8782.call.apply(this_sym8782,[this_sym8782].concat(args8783.slice()));
});
cljs.core.PersistentArrayMap.prototype.cljs$core$IKVReduce$_kv_reduce$arity$3 = (function (coll,f,init){
var this__8806 = this;
var len__8807 = this__8806.arr.length;
var i__8808 = 0;
var init__8809 = init;
while(true){
if((i__8808 < len__8807))
{var init__8810 = f.call(null,init__8809,(this__8806.arr[i__8808]),(this__8806.arr[(i__8808 + 1)]));
if(cljs.core.reduced_QMARK_.call(null,init__8810))
{return cljs.core.deref.call(null,init__8810);
} else
{{
var G__8830 = (i__8808 + 2);
var G__8831 = init__8810;
i__8808 = G__8830;
init__8809 = G__8831;
continue;
}
}
} else
{return null;
}
break;
}
});
cljs.core.PersistentArrayMap.prototype.cljs$core$ICollection$_conj$arity$2 = (function (coll,entry){
var this__8811 = this;
if(cljs.core.vector_QMARK_.call(null,entry))
{return coll.cljs$core$IAssociative$_assoc$arity$3(coll,cljs.core._nth.call(null,entry,0),cljs.core._nth.call(null,entry,1));
} else
{return cljs.core.reduce.call(null,cljs.core._conj,coll,entry);
}
});
cljs.core.PersistentArrayMap.prototype.toString = (function (){
var this__8812 = this;
var this__8813 = this;
return cljs.core.pr_str.call(null,this__8813);
});
cljs.core.PersistentArrayMap.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (coll){
var this__8814 = this;
if((this__8814.cnt > 0))
{var len__8815 = this__8814.arr.length;
var array_map_seq__8816 = (function array_map_seq(i){
return (new cljs.core.LazySeq(null,false,(function (){
if((i < len__8815))
{return cljs.core.cons.call(null,cljs.core.PersistentVector.fromArray([(this__8814.arr[i]),(this__8814.arr[(i + 1)])], true),array_map_seq.call(null,(i + 2)));
} else
{return null;
}
}),null));
});
return array_map_seq__8816.call(null,0);
} else
{return null;
}
});
cljs.core.PersistentArrayMap.prototype.cljs$core$ICounted$_count$arity$1 = (function (coll){
var this__8817 = this;
return this__8817.cnt;
});
cljs.core.PersistentArrayMap.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (coll,other){
var this__8818 = this;
return cljs.core.equiv_map.call(null,coll,other);
});
cljs.core.PersistentArrayMap.prototype.cljs$core$IWithMeta$_with_meta$arity$2 = (function (coll,meta){
var this__8819 = this;
return (new cljs.core.PersistentArrayMap(meta,this__8819.cnt,this__8819.arr,this__8819.__hash));
});
cljs.core.PersistentArrayMap.prototype.cljs$core$IMeta$_meta$arity$1 = (function (coll){
var this__8820 = this;
return this__8820.meta;
});
cljs.core.PersistentArrayMap.prototype.cljs$core$IEmptyableCollection$_empty$arity$1 = (function (coll){
var this__8821 = this;
return cljs.core._with_meta.call(null,cljs.core.PersistentArrayMap.EMPTY,this__8821.meta);
});
cljs.core.PersistentArrayMap.prototype.cljs$core$IMap$_dissoc$arity$2 = (function (coll,k){
var this__8822 = this;
var idx__8823 = cljs.core.array_map_index_of.call(null,coll,k);
if((idx__8823 >= 0))
{var len__8824 = this__8822.arr.length;
var new_len__8825 = (len__8824 - 2);
if((new_len__8825 === 0))
{return coll.cljs$core$IEmptyableCollection$_empty$arity$1(coll);
} else
{var new_arr__8826 = cljs.core.make_array.call(null,new_len__8825);
var s__8827 = 0;
var d__8828 = 0;
while(true){
if((s__8827 >= len__8824))
{return (new cljs.core.PersistentArrayMap(this__8822.meta,(this__8822.cnt - 1),new_arr__8826,null));
} else
{if(cljs.core._EQ_.call(null,k,(this__8822.arr[s__8827])))
{{
var G__8832 = (s__8827 + 2);
var G__8833 = d__8828;
s__8827 = G__8832;
d__8828 = G__8833;
continue;
}
} else
{if("\uFDD0'else")
{(new_arr__8826[d__8828] = (this__8822.arr[s__8827]));
(new_arr__8826[(d__8828 + 1)] = (this__8822.arr[(s__8827 + 1)]));
{
var G__8834 = (s__8827 + 2);
var G__8835 = (d__8828 + 2);
s__8827 = G__8834;
d__8828 = G__8835;
continue;
}
} else
{return null;
}
}
}
break;
}
}
} else
{return coll;
}
});
cljs.core.PersistentArrayMap;
cljs.core.PersistentArrayMap.EMPTY = (new cljs.core.PersistentArrayMap(null,0,[],null));
cljs.core.PersistentArrayMap.HASHMAP_THRESHOLD = 16;
cljs.core.PersistentArrayMap.fromArrays = (function (ks,vs){
var len__8836 = cljs.core.count.call(null,ks);
var i__8837 = 0;
var out__8838 = cljs.core.transient$.call(null,cljs.core.PersistentArrayMap.EMPTY);
while(true){
if((i__8837 < len__8836))
{{
var G__8839 = (i__8837 + 1);
var G__8840 = cljs.core.assoc_BANG_.call(null,out__8838,(ks[i__8837]),(vs[i__8837]));
i__8837 = G__8839;
out__8838 = G__8840;
continue;
}
} else
{return cljs.core.persistent_BANG_.call(null,out__8838);
}
break;
}
});

/**
* @constructor
*/
cljs.core.TransientArrayMap = (function (editable_QMARK_,len,arr){
this.editable_QMARK_ = editable_QMARK_;
this.len = len;
this.arr = arr;
this.cljs$lang$protocol_mask$partition1$ = 14;
this.cljs$lang$protocol_mask$partition0$ = 258;
})
cljs.core.TransientArrayMap.cljs$lang$type = true;
cljs.core.TransientArrayMap.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/TransientArrayMap");
});
cljs.core.TransientArrayMap.prototype.cljs$core$ITransientMap$_dissoc_BANG_$arity$2 = (function (tcoll,key){
var this__8841 = this;
if(cljs.core.truth_(this__8841.editable_QMARK_))
{var idx__8842 = cljs.core.array_map_index_of.call(null,tcoll,key);
if((idx__8842 >= 0))
{(this__8841.arr[idx__8842] = (this__8841.arr[(this__8841.len - 2)]));
(this__8841.arr[(idx__8842 + 1)] = (this__8841.arr[(this__8841.len - 1)]));
var G__8843__8844 = this__8841.arr;
G__8843__8844.pop();
G__8843__8844.pop();
G__8843__8844;
this__8841.len = (this__8841.len - 2);
} else
{}
return tcoll;
} else
{throw (new Error("dissoc! after persistent!"));
}
});
cljs.core.TransientArrayMap.prototype.cljs$core$ITransientAssociative$_assoc_BANG_$arity$3 = (function (tcoll,key,val){
var this__8845 = this;
if(cljs.core.truth_(this__8845.editable_QMARK_))
{var idx__8846 = cljs.core.array_map_index_of.call(null,tcoll,key);
if((idx__8846 === -1))
{if(((this__8845.len + 2) <= (2 * cljs.core.PersistentArrayMap.HASHMAP_THRESHOLD)))
{this__8845.len = (this__8845.len + 2);
this__8845.arr.push(key);
this__8845.arr.push(val);
return tcoll;
} else
{return cljs.core.assoc_BANG_.call(null,cljs.core.array__GT_transient_hash_map.call(null,this__8845.len,this__8845.arr),key,val);
}
} else
{if((val === (this__8845.arr[(idx__8846 + 1)])))
{return tcoll;
} else
{(this__8845.arr[(idx__8846 + 1)] = val);
return tcoll;
}
}
} else
{throw (new Error("assoc! after persistent!"));
}
});
cljs.core.TransientArrayMap.prototype.cljs$core$ITransientCollection$_conj_BANG_$arity$2 = (function (tcoll,o){
var this__8847 = this;
if(cljs.core.truth_(this__8847.editable_QMARK_))
{if((function (){var G__8848__8849 = o;
if(G__8848__8849)
{if((function (){var or__3824__auto____8850 = (G__8848__8849.cljs$lang$protocol_mask$partition0$ & 2048);
if(or__3824__auto____8850)
{return or__3824__auto____8850;
} else
{return G__8848__8849.cljs$core$IMapEntry$;
}
})())
{return true;
} else
{if((!G__8848__8849.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.IMapEntry,G__8848__8849);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.IMapEntry,G__8848__8849);
}
})())
{return tcoll.cljs$core$ITransientAssociative$_assoc_BANG_$arity$3(tcoll,cljs.core.key.call(null,o),cljs.core.val.call(null,o));
} else
{var es__8851 = cljs.core.seq.call(null,o);
var tcoll__8852 = tcoll;
while(true){
var temp__3971__auto____8853 = cljs.core.first.call(null,es__8851);
if(cljs.core.truth_(temp__3971__auto____8853))
{var e__8854 = temp__3971__auto____8853;
{
var G__8860 = cljs.core.next.call(null,es__8851);
var G__8861 = tcoll__8852.cljs$core$ITransientAssociative$_assoc_BANG_$arity$3(tcoll__8852,cljs.core.key.call(null,e__8854),cljs.core.val.call(null,e__8854));
es__8851 = G__8860;
tcoll__8852 = G__8861;
continue;
}
} else
{return tcoll__8852;
}
break;
}
}
} else
{throw (new Error("conj! after persistent!"));
}
});
cljs.core.TransientArrayMap.prototype.cljs$core$ITransientCollection$_persistent_BANG_$arity$1 = (function (tcoll){
var this__8855 = this;
if(cljs.core.truth_(this__8855.editable_QMARK_))
{this__8855.editable_QMARK_ = false;
return (new cljs.core.PersistentArrayMap(null,cljs.core.quot.call(null,this__8855.len,2),this__8855.arr,null));
} else
{throw (new Error("persistent! called twice"));
}
});
cljs.core.TransientArrayMap.prototype.cljs$core$ILookup$_lookup$arity$2 = (function (tcoll,k){
var this__8856 = this;
return tcoll.cljs$core$ILookup$_lookup$arity$3(tcoll,k,null);
});
cljs.core.TransientArrayMap.prototype.cljs$core$ILookup$_lookup$arity$3 = (function (tcoll,k,not_found){
var this__8857 = this;
if(cljs.core.truth_(this__8857.editable_QMARK_))
{var idx__8858 = cljs.core.array_map_index_of.call(null,tcoll,k);
if((idx__8858 === -1))
{return not_found;
} else
{return (this__8857.arr[(idx__8858 + 1)]);
}
} else
{throw (new Error("lookup after persistent!"));
}
});
cljs.core.TransientArrayMap.prototype.cljs$core$ICounted$_count$arity$1 = (function (tcoll){
var this__8859 = this;
if(cljs.core.truth_(this__8859.editable_QMARK_))
{return cljs.core.quot.call(null,this__8859.len,2);
} else
{throw (new Error("count after persistent!"));
}
});
cljs.core.TransientArrayMap;
cljs.core.array__GT_transient_hash_map = (function array__GT_transient_hash_map(len,arr){
var out__8864 = cljs.core.transient$.call(null,cljs.core.ObjMap.EMPTY);
var i__8865 = 0;
while(true){
if((i__8865 < len))
{{
var G__8866 = cljs.core.assoc_BANG_.call(null,out__8864,(arr[i__8865]),(arr[(i__8865 + 1)]));
var G__8867 = (i__8865 + 2);
out__8864 = G__8866;
i__8865 = G__8867;
continue;
}
} else
{return out__8864;
}
break;
}
});

/**
* @constructor
*/
cljs.core.Box = (function (val){
this.val = val;
})
cljs.core.Box.cljs$lang$type = true;
cljs.core.Box.cljs$lang$ctorPrSeq = (function (this__2338__auto__){
return cljs.core.list.call(null,"cljs.core/Box");
});
cljs.core.Box;
cljs.core.key_test = (function key_test(key,other){
if(goog.isString(key))
{return (key === other);
} else
{return cljs.core._EQ_.call(null,key,other);
}
});
cljs.core.mask = (function mask(hash,shift){
return ((hash >>> shift) & 31);
});
cljs.core.clone_and_set = (function() {
var clone_and_set = null;
var clone_and_set__3 = (function (arr,i,a){
var G__8872__8873 = arr.slice();
(G__8872__8873[i] = a);
return G__8872__8873;
});
var clone_and_set__5 = (function (arr,i,a,j,b){
var G__8874__8875 = arr.slice();
(G__8874__8875[i] = a);
(G__8874__8875[j] = b);
return G__8874__8875;
});
clone_and_set = function(arr,i,a,j,b){
switch(arguments.length){
case 3:
return clone_and_set__3.call(this,arr,i,a);
case 5:
return clone_and_set__5.call(this,arr,i,a,j,b);
}
throw('Invalid arity: ' + arguments.length);
};
clone_and_set.cljs$lang$arity$3 = clone_and_set__3;
clone_and_set.cljs$lang$arity$5 = clone_and_set__5;
return clone_and_set;
})()
;
cljs.core.remove_pair = (function remove_pair(arr,i){
var new_arr__8877 = cljs.core.make_array.call(null,(arr.length - 2));
cljs.core.array_copy.call(null,arr,0,new_arr__8877,0,(2 * i));
cljs.core.array_copy.call(null,arr,(2 * (i + 1)),new_arr__8877,(2 * i),(new_arr__8877.length - (2 * i)));
return new_arr__8877;
});
cljs.core.bitmap_indexed_node_index = (function bitmap_indexed_node_index(bitmap,bit){
return cljs.core.bit_count.call(null,(bitmap & (bit - 1)));
});
cljs.core.bitpos = (function bitpos(hash,shift){
return (1 << ((hash >>> shift) & 0x01f));
});
cljs.core.edit_and_set = (function() {
var edit_and_set = null;
var edit_and_set__4 = (function (inode,edit,i,a){
var editable__8880 = inode.ensure_editable(edit);
(editable__8880.arr[i] = a);
return editable__8880;
});
var edit_and_set__6 = (function (inode,edit,i,a,j,b){
var editable__8881 = inode.ensure_editable(edit);
(editable__8881.arr[i] = a);
(editable__8881.arr[j] = b);
return editable__8881;
});
edit_and_set = function(inode,edit,i,a,j,b){
switch(arguments.length){
case 4:
return edit_and_set__4.call(this,inode,edit,i,a);
case 6:
return edit_and_set__6.call(this,inode,edit,i,a,j,b);
}
throw('Invalid arity: ' + arguments.length);
};
edit_and_set.cljs$lang$arity$4 = edit_and_set__4;
edit_and_set.cljs$lang$arity$6 = edit_and_set__6;
return edit_and_set;
})()
;
cljs.core.inode_kv_reduce = (function inode_kv_reduce(arr,f,init){
var len__8888 = arr.length;
var i__8889 = 0;
var init__8890 = init;
while(true){
if((i__8889 < len__8888))
{var init__8893 = (function (){var k__8891 = (arr[i__8889]);
if(!((k__8891 == null)))
{return f.call(null,init__8890,k__8891,(arr[(i__8889 + 1)]));
} else
{var node__8892 = (arr[(i__8889 + 1)]);
if(!((node__8892 == null)))
{return node__8892.kv_reduce(f,init__8890);
} else
{return init__8890;
}
}
})();
if(cljs.core.reduced_QMARK_.call(null,init__8893))
{return cljs.core.deref.call(null,init__8893);
} else
{{
var G__8894 = (i__8889 + 2);
var G__8895 = init__8893;
i__8889 = G__8894;
init__8890 = G__8895;
continue;
}
}
} else
{return init__8890;
}
break;
}
});

/**
* @constructor
*/
cljs.core.BitmapIndexedNode = (function (edit,bitmap,arr){
this.edit = edit;
this.bitmap = bitmap;
this.arr = arr;
})
cljs.core.BitmapIndexedNode.cljs$lang$type = true;
cljs.core.BitmapIndexedNode.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/BitmapIndexedNode");
});
cljs.core.BitmapIndexedNode.prototype.edit_and_remove_pair = (function (e,bit,i){
var this__8896 = this;
var inode__8897 = this;
if((this__8896.bitmap === bit))
{return null;
} else
{var editable__8898 = inode__8897.ensure_editable(e);
var earr__8899 = editable__8898.arr;
var len__8900 = earr__8899.length;
editable__8898.bitmap = (bit ^ editable__8898.bitmap);
cljs.core.array_copy.call(null,earr__8899,(2 * (i + 1)),earr__8899,(2 * i),(len__8900 - (2 * (i + 1))));
(earr__8899[(len__8900 - 2)] = null);
(earr__8899[(len__8900 - 1)] = null);
return editable__8898;
}
});
cljs.core.BitmapIndexedNode.prototype.inode_assoc_BANG_ = (function (edit,shift,hash,key,val,added_leaf_QMARK_){
var this__8901 = this;
var inode__8902 = this;
var bit__8903 = (1 << ((hash >>> shift) & 0x01f));
var idx__8904 = cljs.core.bitmap_indexed_node_index.call(null,this__8901.bitmap,bit__8903);
if(((this__8901.bitmap & bit__8903) === 0))
{var n__8905 = cljs.core.bit_count.call(null,this__8901.bitmap);
if(((2 * n__8905) < this__8901.arr.length))
{var editable__8906 = inode__8902.ensure_editable(edit);
var earr__8907 = editable__8906.arr;
added_leaf_QMARK_.val = true;
cljs.core.array_copy_downward.call(null,earr__8907,(2 * idx__8904),earr__8907,(2 * (idx__8904 + 1)),(2 * (n__8905 - idx__8904)));
(earr__8907[(2 * idx__8904)] = key);
(earr__8907[((2 * idx__8904) + 1)] = val);
editable__8906.bitmap = (editable__8906.bitmap | bit__8903);
return editable__8906;
} else
{if((n__8905 >= 16))
{var nodes__8908 = cljs.core.make_array.call(null,32);
var jdx__8909 = ((hash >>> shift) & 0x01f);
(nodes__8908[jdx__8909] = cljs.core.BitmapIndexedNode.EMPTY.inode_assoc_BANG_(edit,(shift + 5),hash,key,val,added_leaf_QMARK_));
var i__8910 = 0;
var j__8911 = 0;
while(true){
if((i__8910 < 32))
{if((((this__8901.bitmap >>> i__8910) & 1) === 0))
{{
var G__8964 = (i__8910 + 1);
var G__8965 = j__8911;
i__8910 = G__8964;
j__8911 = G__8965;
continue;
}
} else
{(nodes__8908[i__8910] = ((!(((this__8901.arr[j__8911]) == null)))?cljs.core.BitmapIndexedNode.EMPTY.inode_assoc_BANG_(edit,(shift + 5),cljs.core.hash.call(null,(this__8901.arr[j__8911])),(this__8901.arr[j__8911]),(this__8901.arr[(j__8911 + 1)]),added_leaf_QMARK_):(this__8901.arr[(j__8911 + 1)])));
{
var G__8966 = (i__8910 + 1);
var G__8967 = (j__8911 + 2);
i__8910 = G__8966;
j__8911 = G__8967;
continue;
}
}
} else
{}
break;
}
return (new cljs.core.ArrayNode(edit,(n__8905 + 1),nodes__8908));
} else
{if("\uFDD0'else")
{var new_arr__8912 = cljs.core.make_array.call(null,(2 * (n__8905 + 4)));
cljs.core.array_copy.call(null,this__8901.arr,0,new_arr__8912,0,(2 * idx__8904));
(new_arr__8912[(2 * idx__8904)] = key);
(new_arr__8912[((2 * idx__8904) + 1)] = val);
cljs.core.array_copy.call(null,this__8901.arr,(2 * idx__8904),new_arr__8912,(2 * (idx__8904 + 1)),(2 * (n__8905 - idx__8904)));
added_leaf_QMARK_.val = true;
var editable__8913 = inode__8902.ensure_editable(edit);
editable__8913.arr = new_arr__8912;
editable__8913.bitmap = (editable__8913.bitmap | bit__8903);
return editable__8913;
} else
{return null;
}
}
}
} else
{var key_or_nil__8914 = (this__8901.arr[(2 * idx__8904)]);
var val_or_node__8915 = (this__8901.arr[((2 * idx__8904) + 1)]);
if((key_or_nil__8914 == null))
{var n__8916 = val_or_node__8915.inode_assoc_BANG_(edit,(shift + 5),hash,key,val,added_leaf_QMARK_);
if((n__8916 === val_or_node__8915))
{return inode__8902;
} else
{return cljs.core.edit_and_set.call(null,inode__8902,edit,((2 * idx__8904) + 1),n__8916);
}
} else
{if(cljs.core.key_test.call(null,key,key_or_nil__8914))
{if((val === val_or_node__8915))
{return inode__8902;
} else
{return cljs.core.edit_and_set.call(null,inode__8902,edit,((2 * idx__8904) + 1),val);
}
} else
{if("\uFDD0'else")
{added_leaf_QMARK_.val = true;
return cljs.core.edit_and_set.call(null,inode__8902,edit,(2 * idx__8904),null,((2 * idx__8904) + 1),cljs.core.create_node.call(null,edit,(shift + 5),key_or_nil__8914,val_or_node__8915,hash,key,val));
} else
{return null;
}
}
}
}
});
cljs.core.BitmapIndexedNode.prototype.inode_seq = (function (){
var this__8917 = this;
var inode__8918 = this;
return cljs.core.create_inode_seq.call(null,this__8917.arr);
});
cljs.core.BitmapIndexedNode.prototype.inode_without_BANG_ = (function (edit,shift,hash,key,removed_leaf_QMARK_){
var this__8919 = this;
var inode__8920 = this;
var bit__8921 = (1 << ((hash >>> shift) & 0x01f));
if(((this__8919.bitmap & bit__8921) === 0))
{return inode__8920;
} else
{var idx__8922 = cljs.core.bitmap_indexed_node_index.call(null,this__8919.bitmap,bit__8921);
var key_or_nil__8923 = (this__8919.arr[(2 * idx__8922)]);
var val_or_node__8924 = (this__8919.arr[((2 * idx__8922) + 1)]);
if((key_or_nil__8923 == null))
{var n__8925 = val_or_node__8924.inode_without_BANG_(edit,(shift + 5),hash,key,removed_leaf_QMARK_);
if((n__8925 === val_or_node__8924))
{return inode__8920;
} else
{if(!((n__8925 == null)))
{return cljs.core.edit_and_set.call(null,inode__8920,edit,((2 * idx__8922) + 1),n__8925);
} else
{if((this__8919.bitmap === bit__8921))
{return null;
} else
{if("\uFDD0'else")
{return inode__8920.edit_and_remove_pair(edit,bit__8921,idx__8922);
} else
{return null;
}
}
}
}
} else
{if(cljs.core.key_test.call(null,key,key_or_nil__8923))
{(removed_leaf_QMARK_[0] = true);
return inode__8920.edit_and_remove_pair(edit,bit__8921,idx__8922);
} else
{if("\uFDD0'else")
{return inode__8920;
} else
{return null;
}
}
}
}
});
cljs.core.BitmapIndexedNode.prototype.ensure_editable = (function (e){
var this__8926 = this;
var inode__8927 = this;
if((e === this__8926.edit))
{return inode__8927;
} else
{var n__8928 = cljs.core.bit_count.call(null,this__8926.bitmap);
var new_arr__8929 = cljs.core.make_array.call(null,(((n__8928 < 0))?4:(2 * (n__8928 + 1))));
cljs.core.array_copy.call(null,this__8926.arr,0,new_arr__8929,0,(2 * n__8928));
return (new cljs.core.BitmapIndexedNode(e,this__8926.bitmap,new_arr__8929));
}
});
cljs.core.BitmapIndexedNode.prototype.kv_reduce = (function (f,init){
var this__8930 = this;
var inode__8931 = this;
return cljs.core.inode_kv_reduce.call(null,this__8930.arr,f,init);
});
cljs.core.BitmapIndexedNode.prototype.inode_find = (function (shift,hash,key,not_found){
var this__8932 = this;
var inode__8933 = this;
var bit__8934 = (1 << ((hash >>> shift) & 0x01f));
if(((this__8932.bitmap & bit__8934) === 0))
{return not_found;
} else
{var idx__8935 = cljs.core.bitmap_indexed_node_index.call(null,this__8932.bitmap,bit__8934);
var key_or_nil__8936 = (this__8932.arr[(2 * idx__8935)]);
var val_or_node__8937 = (this__8932.arr[((2 * idx__8935) + 1)]);
if((key_or_nil__8936 == null))
{return val_or_node__8937.inode_find((shift + 5),hash,key,not_found);
} else
{if(cljs.core.key_test.call(null,key,key_or_nil__8936))
{return cljs.core.PersistentVector.fromArray([key_or_nil__8936,val_or_node__8937], true);
} else
{if("\uFDD0'else")
{return not_found;
} else
{return null;
}
}
}
}
});
cljs.core.BitmapIndexedNode.prototype.inode_without = (function (shift,hash,key){
var this__8938 = this;
var inode__8939 = this;
var bit__8940 = (1 << ((hash >>> shift) & 0x01f));
if(((this__8938.bitmap & bit__8940) === 0))
{return inode__8939;
} else
{var idx__8941 = cljs.core.bitmap_indexed_node_index.call(null,this__8938.bitmap,bit__8940);
var key_or_nil__8942 = (this__8938.arr[(2 * idx__8941)]);
var val_or_node__8943 = (this__8938.arr[((2 * idx__8941) + 1)]);
if((key_or_nil__8942 == null))
{var n__8944 = val_or_node__8943.inode_without((shift + 5),hash,key);
if((n__8944 === val_or_node__8943))
{return inode__8939;
} else
{if(!((n__8944 == null)))
{return (new cljs.core.BitmapIndexedNode(null,this__8938.bitmap,cljs.core.clone_and_set.call(null,this__8938.arr,((2 * idx__8941) + 1),n__8944)));
} else
{if((this__8938.bitmap === bit__8940))
{return null;
} else
{if("\uFDD0'else")
{return (new cljs.core.BitmapIndexedNode(null,(this__8938.bitmap ^ bit__8940),cljs.core.remove_pair.call(null,this__8938.arr,idx__8941)));
} else
{return null;
}
}
}
}
} else
{if(cljs.core.key_test.call(null,key,key_or_nil__8942))
{return (new cljs.core.BitmapIndexedNode(null,(this__8938.bitmap ^ bit__8940),cljs.core.remove_pair.call(null,this__8938.arr,idx__8941)));
} else
{if("\uFDD0'else")
{return inode__8939;
} else
{return null;
}
}
}
}
});
cljs.core.BitmapIndexedNode.prototype.inode_assoc = (function (shift,hash,key,val,added_leaf_QMARK_){
var this__8945 = this;
var inode__8946 = this;
var bit__8947 = (1 << ((hash >>> shift) & 0x01f));
var idx__8948 = cljs.core.bitmap_indexed_node_index.call(null,this__8945.bitmap,bit__8947);
if(((this__8945.bitmap & bit__8947) === 0))
{var n__8949 = cljs.core.bit_count.call(null,this__8945.bitmap);
if((n__8949 >= 16))
{var nodes__8950 = cljs.core.make_array.call(null,32);
var jdx__8951 = ((hash >>> shift) & 0x01f);
(nodes__8950[jdx__8951] = cljs.core.BitmapIndexedNode.EMPTY.inode_assoc((shift + 5),hash,key,val,added_leaf_QMARK_));
var i__8952 = 0;
var j__8953 = 0;
while(true){
if((i__8952 < 32))
{if((((this__8945.bitmap >>> i__8952) & 1) === 0))
{{
var G__8968 = (i__8952 + 1);
var G__8969 = j__8953;
i__8952 = G__8968;
j__8953 = G__8969;
continue;
}
} else
{(nodes__8950[i__8952] = ((!(((this__8945.arr[j__8953]) == null)))?cljs.core.BitmapIndexedNode.EMPTY.inode_assoc((shift + 5),cljs.core.hash.call(null,(this__8945.arr[j__8953])),(this__8945.arr[j__8953]),(this__8945.arr[(j__8953 + 1)]),added_leaf_QMARK_):(this__8945.arr[(j__8953 + 1)])));
{
var G__8970 = (i__8952 + 1);
var G__8971 = (j__8953 + 2);
i__8952 = G__8970;
j__8953 = G__8971;
continue;
}
}
} else
{}
break;
}
return (new cljs.core.ArrayNode(null,(n__8949 + 1),nodes__8950));
} else
{var new_arr__8954 = cljs.core.make_array.call(null,(2 * (n__8949 + 1)));
cljs.core.array_copy.call(null,this__8945.arr,0,new_arr__8954,0,(2 * idx__8948));
(new_arr__8954[(2 * idx__8948)] = key);
(new_arr__8954[((2 * idx__8948) + 1)] = val);
cljs.core.array_copy.call(null,this__8945.arr,(2 * idx__8948),new_arr__8954,(2 * (idx__8948 + 1)),(2 * (n__8949 - idx__8948)));
added_leaf_QMARK_.val = true;
return (new cljs.core.BitmapIndexedNode(null,(this__8945.bitmap | bit__8947),new_arr__8954));
}
} else
{var key_or_nil__8955 = (this__8945.arr[(2 * idx__8948)]);
var val_or_node__8956 = (this__8945.arr[((2 * idx__8948) + 1)]);
if((key_or_nil__8955 == null))
{var n__8957 = val_or_node__8956.inode_assoc((shift + 5),hash,key,val,added_leaf_QMARK_);
if((n__8957 === val_or_node__8956))
{return inode__8946;
} else
{return (new cljs.core.BitmapIndexedNode(null,this__8945.bitmap,cljs.core.clone_and_set.call(null,this__8945.arr,((2 * idx__8948) + 1),n__8957)));
}
} else
{if(cljs.core.key_test.call(null,key,key_or_nil__8955))
{if((val === val_or_node__8956))
{return inode__8946;
} else
{return (new cljs.core.BitmapIndexedNode(null,this__8945.bitmap,cljs.core.clone_and_set.call(null,this__8945.arr,((2 * idx__8948) + 1),val)));
}
} else
{if("\uFDD0'else")
{added_leaf_QMARK_.val = true;
return (new cljs.core.BitmapIndexedNode(null,this__8945.bitmap,cljs.core.clone_and_set.call(null,this__8945.arr,(2 * idx__8948),null,((2 * idx__8948) + 1),cljs.core.create_node.call(null,(shift + 5),key_or_nil__8955,val_or_node__8956,hash,key,val))));
} else
{return null;
}
}
}
}
});
cljs.core.BitmapIndexedNode.prototype.inode_lookup = (function (shift,hash,key,not_found){
var this__8958 = this;
var inode__8959 = this;
var bit__8960 = (1 << ((hash >>> shift) & 0x01f));
if(((this__8958.bitmap & bit__8960) === 0))
{return not_found;
} else
{var idx__8961 = cljs.core.bitmap_indexed_node_index.call(null,this__8958.bitmap,bit__8960);
var key_or_nil__8962 = (this__8958.arr[(2 * idx__8961)]);
var val_or_node__8963 = (this__8958.arr[((2 * idx__8961) + 1)]);
if((key_or_nil__8962 == null))
{return val_or_node__8963.inode_lookup((shift + 5),hash,key,not_found);
} else
{if(cljs.core.key_test.call(null,key,key_or_nil__8962))
{return val_or_node__8963;
} else
{if("\uFDD0'else")
{return not_found;
} else
{return null;
}
}
}
}
});
cljs.core.BitmapIndexedNode;
cljs.core.BitmapIndexedNode.EMPTY = (new cljs.core.BitmapIndexedNode(null,0,cljs.core.make_array.call(null,0)));
cljs.core.pack_array_node = (function pack_array_node(array_node,edit,idx){
var arr__8979 = array_node.arr;
var len__8980 = (2 * (array_node.cnt - 1));
var new_arr__8981 = cljs.core.make_array.call(null,len__8980);
var i__8982 = 0;
var j__8983 = 1;
var bitmap__8984 = 0;
while(true){
if((i__8982 < len__8980))
{if((function (){var and__3822__auto____8985 = !((i__8982 === idx));
if(and__3822__auto____8985)
{return !(((arr__8979[i__8982]) == null));
} else
{return and__3822__auto____8985;
}
})())
{(new_arr__8981[j__8983] = (arr__8979[i__8982]));
{
var G__8986 = (i__8982 + 1);
var G__8987 = (j__8983 + 2);
var G__8988 = (bitmap__8984 | (1 << i__8982));
i__8982 = G__8986;
j__8983 = G__8987;
bitmap__8984 = G__8988;
continue;
}
} else
{{
var G__8989 = (i__8982 + 1);
var G__8990 = j__8983;
var G__8991 = bitmap__8984;
i__8982 = G__8989;
j__8983 = G__8990;
bitmap__8984 = G__8991;
continue;
}
}
} else
{return (new cljs.core.BitmapIndexedNode(edit,bitmap__8984,new_arr__8981));
}
break;
}
});

/**
* @constructor
*/
cljs.core.ArrayNode = (function (edit,cnt,arr){
this.edit = edit;
this.cnt = cnt;
this.arr = arr;
})
cljs.core.ArrayNode.cljs$lang$type = true;
cljs.core.ArrayNode.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/ArrayNode");
});
cljs.core.ArrayNode.prototype.inode_assoc_BANG_ = (function (edit,shift,hash,key,val,added_leaf_QMARK_){
var this__8992 = this;
var inode__8993 = this;
var idx__8994 = ((hash >>> shift) & 0x01f);
var node__8995 = (this__8992.arr[idx__8994]);
if((node__8995 == null))
{var editable__8996 = cljs.core.edit_and_set.call(null,inode__8993,edit,idx__8994,cljs.core.BitmapIndexedNode.EMPTY.inode_assoc_BANG_(edit,(shift + 5),hash,key,val,added_leaf_QMARK_));
editable__8996.cnt = (editable__8996.cnt + 1);
return editable__8996;
} else
{var n__8997 = node__8995.inode_assoc_BANG_(edit,(shift + 5),hash,key,val,added_leaf_QMARK_);
if((n__8997 === node__8995))
{return inode__8993;
} else
{return cljs.core.edit_and_set.call(null,inode__8993,edit,idx__8994,n__8997);
}
}
});
cljs.core.ArrayNode.prototype.inode_seq = (function (){
var this__8998 = this;
var inode__8999 = this;
return cljs.core.create_array_node_seq.call(null,this__8998.arr);
});
cljs.core.ArrayNode.prototype.inode_without_BANG_ = (function (edit,shift,hash,key,removed_leaf_QMARK_){
var this__9000 = this;
var inode__9001 = this;
var idx__9002 = ((hash >>> shift) & 0x01f);
var node__9003 = (this__9000.arr[idx__9002]);
if((node__9003 == null))
{return inode__9001;
} else
{var n__9004 = node__9003.inode_without_BANG_(edit,(shift + 5),hash,key,removed_leaf_QMARK_);
if((n__9004 === node__9003))
{return inode__9001;
} else
{if((n__9004 == null))
{if((this__9000.cnt <= 8))
{return cljs.core.pack_array_node.call(null,inode__9001,edit,idx__9002);
} else
{var editable__9005 = cljs.core.edit_and_set.call(null,inode__9001,edit,idx__9002,n__9004);
editable__9005.cnt = (editable__9005.cnt - 1);
return editable__9005;
}
} else
{if("\uFDD0'else")
{return cljs.core.edit_and_set.call(null,inode__9001,edit,idx__9002,n__9004);
} else
{return null;
}
}
}
}
});
cljs.core.ArrayNode.prototype.ensure_editable = (function (e){
var this__9006 = this;
var inode__9007 = this;
if((e === this__9006.edit))
{return inode__9007;
} else
{return (new cljs.core.ArrayNode(e,this__9006.cnt,this__9006.arr.slice()));
}
});
cljs.core.ArrayNode.prototype.kv_reduce = (function (f,init){
var this__9008 = this;
var inode__9009 = this;
var len__9010 = this__9008.arr.length;
var i__9011 = 0;
var init__9012 = init;
while(true){
if((i__9011 < len__9010))
{var node__9013 = (this__9008.arr[i__9011]);
if(!((node__9013 == null)))
{var init__9014 = node__9013.kv_reduce(f,init__9012);
if(cljs.core.reduced_QMARK_.call(null,init__9014))
{return cljs.core.deref.call(null,init__9014);
} else
{{
var G__9033 = (i__9011 + 1);
var G__9034 = init__9014;
i__9011 = G__9033;
init__9012 = G__9034;
continue;
}
}
} else
{return null;
}
} else
{return init__9012;
}
break;
}
});
cljs.core.ArrayNode.prototype.inode_find = (function (shift,hash,key,not_found){
var this__9015 = this;
var inode__9016 = this;
var idx__9017 = ((hash >>> shift) & 0x01f);
var node__9018 = (this__9015.arr[idx__9017]);
if(!((node__9018 == null)))
{return node__9018.inode_find((shift + 5),hash,key,not_found);
} else
{return not_found;
}
});
cljs.core.ArrayNode.prototype.inode_without = (function (shift,hash,key){
var this__9019 = this;
var inode__9020 = this;
var idx__9021 = ((hash >>> shift) & 0x01f);
var node__9022 = (this__9019.arr[idx__9021]);
if(!((node__9022 == null)))
{var n__9023 = node__9022.inode_without((shift + 5),hash,key);
if((n__9023 === node__9022))
{return inode__9020;
} else
{if((n__9023 == null))
{if((this__9019.cnt <= 8))
{return cljs.core.pack_array_node.call(null,inode__9020,null,idx__9021);
} else
{return (new cljs.core.ArrayNode(null,(this__9019.cnt - 1),cljs.core.clone_and_set.call(null,this__9019.arr,idx__9021,n__9023)));
}
} else
{if("\uFDD0'else")
{return (new cljs.core.ArrayNode(null,this__9019.cnt,cljs.core.clone_and_set.call(null,this__9019.arr,idx__9021,n__9023)));
} else
{return null;
}
}
}
} else
{return inode__9020;
}
});
cljs.core.ArrayNode.prototype.inode_assoc = (function (shift,hash,key,val,added_leaf_QMARK_){
var this__9024 = this;
var inode__9025 = this;
var idx__9026 = ((hash >>> shift) & 0x01f);
var node__9027 = (this__9024.arr[idx__9026]);
if((node__9027 == null))
{return (new cljs.core.ArrayNode(null,(this__9024.cnt + 1),cljs.core.clone_and_set.call(null,this__9024.arr,idx__9026,cljs.core.BitmapIndexedNode.EMPTY.inode_assoc((shift + 5),hash,key,val,added_leaf_QMARK_))));
} else
{var n__9028 = node__9027.inode_assoc((shift + 5),hash,key,val,added_leaf_QMARK_);
if((n__9028 === node__9027))
{return inode__9025;
} else
{return (new cljs.core.ArrayNode(null,this__9024.cnt,cljs.core.clone_and_set.call(null,this__9024.arr,idx__9026,n__9028)));
}
}
});
cljs.core.ArrayNode.prototype.inode_lookup = (function (shift,hash,key,not_found){
var this__9029 = this;
var inode__9030 = this;
var idx__9031 = ((hash >>> shift) & 0x01f);
var node__9032 = (this__9029.arr[idx__9031]);
if(!((node__9032 == null)))
{return node__9032.inode_lookup((shift + 5),hash,key,not_found);
} else
{return not_found;
}
});
cljs.core.ArrayNode;
cljs.core.hash_collision_node_find_index = (function hash_collision_node_find_index(arr,cnt,key){
var lim__9037 = (2 * cnt);
var i__9038 = 0;
while(true){
if((i__9038 < lim__9037))
{if(cljs.core.key_test.call(null,key,(arr[i__9038])))
{return i__9038;
} else
{{
var G__9039 = (i__9038 + 2);
i__9038 = G__9039;
continue;
}
}
} else
{return -1;
}
break;
}
});

/**
* @constructor
*/
cljs.core.HashCollisionNode = (function (edit,collision_hash,cnt,arr){
this.edit = edit;
this.collision_hash = collision_hash;
this.cnt = cnt;
this.arr = arr;
})
cljs.core.HashCollisionNode.cljs$lang$type = true;
cljs.core.HashCollisionNode.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/HashCollisionNode");
});
cljs.core.HashCollisionNode.prototype.inode_assoc_BANG_ = (function (edit,shift,hash,key,val,added_leaf_QMARK_){
var this__9040 = this;
var inode__9041 = this;
if((hash === this__9040.collision_hash))
{var idx__9042 = cljs.core.hash_collision_node_find_index.call(null,this__9040.arr,this__9040.cnt,key);
if((idx__9042 === -1))
{if((this__9040.arr.length > (2 * this__9040.cnt)))
{var editable__9043 = cljs.core.edit_and_set.call(null,inode__9041,edit,(2 * this__9040.cnt),key,((2 * this__9040.cnt) + 1),val);
added_leaf_QMARK_.val = true;
editable__9043.cnt = (editable__9043.cnt + 1);
return editable__9043;
} else
{var len__9044 = this__9040.arr.length;
var new_arr__9045 = cljs.core.make_array.call(null,(len__9044 + 2));
cljs.core.array_copy.call(null,this__9040.arr,0,new_arr__9045,0,len__9044);
(new_arr__9045[len__9044] = key);
(new_arr__9045[(len__9044 + 1)] = val);
added_leaf_QMARK_.val = true;
return inode__9041.ensure_editable_array(edit,(this__9040.cnt + 1),new_arr__9045);
}
} else
{if(((this__9040.arr[(idx__9042 + 1)]) === val))
{return inode__9041;
} else
{return cljs.core.edit_and_set.call(null,inode__9041,edit,(idx__9042 + 1),val);
}
}
} else
{return (new cljs.core.BitmapIndexedNode(edit,(1 << ((this__9040.collision_hash >>> shift) & 0x01f)),[null,inode__9041,null,null])).inode_assoc_BANG_(edit,shift,hash,key,val,added_leaf_QMARK_);
}
});
cljs.core.HashCollisionNode.prototype.inode_seq = (function (){
var this__9046 = this;
var inode__9047 = this;
return cljs.core.create_inode_seq.call(null,this__9046.arr);
});
cljs.core.HashCollisionNode.prototype.inode_without_BANG_ = (function (edit,shift,hash,key,removed_leaf_QMARK_){
var this__9048 = this;
var inode__9049 = this;
var idx__9050 = cljs.core.hash_collision_node_find_index.call(null,this__9048.arr,this__9048.cnt,key);
if((idx__9050 === -1))
{return inode__9049;
} else
{(removed_leaf_QMARK_[0] = true);
if((this__9048.cnt === 1))
{return null;
} else
{var editable__9051 = inode__9049.ensure_editable(edit);
var earr__9052 = editable__9051.arr;
(earr__9052[idx__9050] = (earr__9052[((2 * this__9048.cnt) - 2)]));
(earr__9052[(idx__9050 + 1)] = (earr__9052[((2 * this__9048.cnt) - 1)]));
(earr__9052[((2 * this__9048.cnt) - 1)] = null);
(earr__9052[((2 * this__9048.cnt) - 2)] = null);
editable__9051.cnt = (editable__9051.cnt - 1);
return editable__9051;
}
}
});
cljs.core.HashCollisionNode.prototype.ensure_editable = (function (e){
var this__9053 = this;
var inode__9054 = this;
if((e === this__9053.edit))
{return inode__9054;
} else
{var new_arr__9055 = cljs.core.make_array.call(null,(2 * (this__9053.cnt + 1)));
cljs.core.array_copy.call(null,this__9053.arr,0,new_arr__9055,0,(2 * this__9053.cnt));
return (new cljs.core.HashCollisionNode(e,this__9053.collision_hash,this__9053.cnt,new_arr__9055));
}
});
cljs.core.HashCollisionNode.prototype.kv_reduce = (function (f,init){
var this__9056 = this;
var inode__9057 = this;
return cljs.core.inode_kv_reduce.call(null,this__9056.arr,f,init);
});
cljs.core.HashCollisionNode.prototype.inode_find = (function (shift,hash,key,not_found){
var this__9058 = this;
var inode__9059 = this;
var idx__9060 = cljs.core.hash_collision_node_find_index.call(null,this__9058.arr,this__9058.cnt,key);
if((idx__9060 < 0))
{return not_found;
} else
{if(cljs.core.key_test.call(null,key,(this__9058.arr[idx__9060])))
{return cljs.core.PersistentVector.fromArray([(this__9058.arr[idx__9060]),(this__9058.arr[(idx__9060 + 1)])], true);
} else
{if("\uFDD0'else")
{return not_found;
} else
{return null;
}
}
}
});
cljs.core.HashCollisionNode.prototype.inode_without = (function (shift,hash,key){
var this__9061 = this;
var inode__9062 = this;
var idx__9063 = cljs.core.hash_collision_node_find_index.call(null,this__9061.arr,this__9061.cnt,key);
if((idx__9063 === -1))
{return inode__9062;
} else
{if((this__9061.cnt === 1))
{return null;
} else
{if("\uFDD0'else")
{return (new cljs.core.HashCollisionNode(null,this__9061.collision_hash,(this__9061.cnt - 1),cljs.core.remove_pair.call(null,this__9061.arr,cljs.core.quot.call(null,idx__9063,2))));
} else
{return null;
}
}
}
});
cljs.core.HashCollisionNode.prototype.inode_assoc = (function (shift,hash,key,val,added_leaf_QMARK_){
var this__9064 = this;
var inode__9065 = this;
if((hash === this__9064.collision_hash))
{var idx__9066 = cljs.core.hash_collision_node_find_index.call(null,this__9064.arr,this__9064.cnt,key);
if((idx__9066 === -1))
{var len__9067 = this__9064.arr.length;
var new_arr__9068 = cljs.core.make_array.call(null,(len__9067 + 2));
cljs.core.array_copy.call(null,this__9064.arr,0,new_arr__9068,0,len__9067);
(new_arr__9068[len__9067] = key);
(new_arr__9068[(len__9067 + 1)] = val);
added_leaf_QMARK_.val = true;
return (new cljs.core.HashCollisionNode(null,this__9064.collision_hash,(this__9064.cnt + 1),new_arr__9068));
} else
{if(cljs.core._EQ_.call(null,(this__9064.arr[idx__9066]),val))
{return inode__9065;
} else
{return (new cljs.core.HashCollisionNode(null,this__9064.collision_hash,this__9064.cnt,cljs.core.clone_and_set.call(null,this__9064.arr,(idx__9066 + 1),val)));
}
}
} else
{return (new cljs.core.BitmapIndexedNode(null,(1 << ((this__9064.collision_hash >>> shift) & 0x01f)),[null,inode__9065])).inode_assoc(shift,hash,key,val,added_leaf_QMARK_);
}
});
cljs.core.HashCollisionNode.prototype.inode_lookup = (function (shift,hash,key,not_found){
var this__9069 = this;
var inode__9070 = this;
var idx__9071 = cljs.core.hash_collision_node_find_index.call(null,this__9069.arr,this__9069.cnt,key);
if((idx__9071 < 0))
{return not_found;
} else
{if(cljs.core.key_test.call(null,key,(this__9069.arr[idx__9071])))
{return (this__9069.arr[(idx__9071 + 1)]);
} else
{if("\uFDD0'else")
{return not_found;
} else
{return null;
}
}
}
});
cljs.core.HashCollisionNode.prototype.ensure_editable_array = (function (e,count,array){
var this__9072 = this;
var inode__9073 = this;
if((e === this__9072.edit))
{this__9072.arr = array;
this__9072.cnt = count;
return inode__9073;
} else
{return (new cljs.core.HashCollisionNode(this__9072.edit,this__9072.collision_hash,count,array));
}
});
cljs.core.HashCollisionNode;
cljs.core.create_node = (function() {
var create_node = null;
var create_node__6 = (function (shift,key1,val1,key2hash,key2,val2){
var key1hash__9078 = cljs.core.hash.call(null,key1);
if((key1hash__9078 === key2hash))
{return (new cljs.core.HashCollisionNode(null,key1hash__9078,2,[key1,val1,key2,val2]));
} else
{var added_leaf_QMARK___9079 = (new cljs.core.Box(false));
return cljs.core.BitmapIndexedNode.EMPTY.inode_assoc(shift,key1hash__9078,key1,val1,added_leaf_QMARK___9079).inode_assoc(shift,key2hash,key2,val2,added_leaf_QMARK___9079);
}
});
var create_node__7 = (function (edit,shift,key1,val1,key2hash,key2,val2){
var key1hash__9080 = cljs.core.hash.call(null,key1);
if((key1hash__9080 === key2hash))
{return (new cljs.core.HashCollisionNode(null,key1hash__9080,2,[key1,val1,key2,val2]));
} else
{var added_leaf_QMARK___9081 = (new cljs.core.Box(false));
return cljs.core.BitmapIndexedNode.EMPTY.inode_assoc_BANG_(edit,shift,key1hash__9080,key1,val1,added_leaf_QMARK___9081).inode_assoc_BANG_(edit,shift,key2hash,key2,val2,added_leaf_QMARK___9081);
}
});
create_node = function(edit,shift,key1,val1,key2hash,key2,val2){
switch(arguments.length){
case 6:
return create_node__6.call(this,edit,shift,key1,val1,key2hash,key2);
case 7:
return create_node__7.call(this,edit,shift,key1,val1,key2hash,key2,val2);
}
throw('Invalid arity: ' + arguments.length);
};
create_node.cljs$lang$arity$6 = create_node__6;
create_node.cljs$lang$arity$7 = create_node__7;
return create_node;
})()
;

/**
* @constructor
*/
cljs.core.NodeSeq = (function (meta,nodes,i,s,__hash){
this.meta = meta;
this.nodes = nodes;
this.i = i;
this.s = s;
this.__hash = __hash;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 31850572;
})
cljs.core.NodeSeq.cljs$lang$type = true;
cljs.core.NodeSeq.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/NodeSeq");
});
cljs.core.NodeSeq.prototype.cljs$core$IHash$_hash$arity$1 = (function (coll){
var this__9082 = this;
var h__2220__auto____9083 = this__9082.__hash;
if(!((h__2220__auto____9083 == null)))
{return h__2220__auto____9083;
} else
{var h__2220__auto____9084 = cljs.core.hash_coll.call(null,coll);
this__9082.__hash = h__2220__auto____9084;
return h__2220__auto____9084;
}
});
cljs.core.NodeSeq.prototype.cljs$core$ICollection$_conj$arity$2 = (function (coll,o){
var this__9085 = this;
return cljs.core.cons.call(null,o,coll);
});
cljs.core.NodeSeq.prototype.toString = (function (){
var this__9086 = this;
var this__9087 = this;
return cljs.core.pr_str.call(null,this__9087);
});
cljs.core.NodeSeq.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (this$){
var this__9088 = this;
return this$;
});
cljs.core.NodeSeq.prototype.cljs$core$ISeq$_first$arity$1 = (function (coll){
var this__9089 = this;
if((this__9089.s == null))
{return cljs.core.PersistentVector.fromArray([(this__9089.nodes[this__9089.i]),(this__9089.nodes[(this__9089.i + 1)])], true);
} else
{return cljs.core.first.call(null,this__9089.s);
}
});
cljs.core.NodeSeq.prototype.cljs$core$ISeq$_rest$arity$1 = (function (coll){
var this__9090 = this;
if((this__9090.s == null))
{return cljs.core.create_inode_seq.call(null,this__9090.nodes,(this__9090.i + 2),null);
} else
{return cljs.core.create_inode_seq.call(null,this__9090.nodes,this__9090.i,cljs.core.next.call(null,this__9090.s));
}
});
cljs.core.NodeSeq.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (coll,other){
var this__9091 = this;
return cljs.core.equiv_sequential.call(null,coll,other);
});
cljs.core.NodeSeq.prototype.cljs$core$IWithMeta$_with_meta$arity$2 = (function (coll,meta){
var this__9092 = this;
return (new cljs.core.NodeSeq(meta,this__9092.nodes,this__9092.i,this__9092.s,this__9092.__hash));
});
cljs.core.NodeSeq.prototype.cljs$core$IMeta$_meta$arity$1 = (function (coll){
var this__9093 = this;
return this__9093.meta;
});
cljs.core.NodeSeq.prototype.cljs$core$IEmptyableCollection$_empty$arity$1 = (function (coll){
var this__9094 = this;
return cljs.core.with_meta.call(null,cljs.core.List.EMPTY,this__9094.meta);
});
cljs.core.NodeSeq;
cljs.core.create_inode_seq = (function() {
var create_inode_seq = null;
var create_inode_seq__1 = (function (nodes){
return create_inode_seq.call(null,nodes,0,null);
});
var create_inode_seq__3 = (function (nodes,i,s){
if((s == null))
{var len__9101 = nodes.length;
var j__9102 = i;
while(true){
if((j__9102 < len__9101))
{if(!(((nodes[j__9102]) == null)))
{return (new cljs.core.NodeSeq(null,nodes,j__9102,null,null));
} else
{var temp__3971__auto____9103 = (nodes[(j__9102 + 1)]);
if(cljs.core.truth_(temp__3971__auto____9103))
{var node__9104 = temp__3971__auto____9103;
var temp__3971__auto____9105 = node__9104.inode_seq();
if(cljs.core.truth_(temp__3971__auto____9105))
{var node_seq__9106 = temp__3971__auto____9105;
return (new cljs.core.NodeSeq(null,nodes,(j__9102 + 2),node_seq__9106,null));
} else
{{
var G__9107 = (j__9102 + 2);
j__9102 = G__9107;
continue;
}
}
} else
{{
var G__9108 = (j__9102 + 2);
j__9102 = G__9108;
continue;
}
}
}
} else
{return null;
}
break;
}
} else
{return (new cljs.core.NodeSeq(null,nodes,i,s,null));
}
});
create_inode_seq = function(nodes,i,s){
switch(arguments.length){
case 1:
return create_inode_seq__1.call(this,nodes);
case 3:
return create_inode_seq__3.call(this,nodes,i,s);
}
throw('Invalid arity: ' + arguments.length);
};
create_inode_seq.cljs$lang$arity$1 = create_inode_seq__1;
create_inode_seq.cljs$lang$arity$3 = create_inode_seq__3;
return create_inode_seq;
})()
;

/**
* @constructor
*/
cljs.core.ArrayNodeSeq = (function (meta,nodes,i,s,__hash){
this.meta = meta;
this.nodes = nodes;
this.i = i;
this.s = s;
this.__hash = __hash;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 31850572;
})
cljs.core.ArrayNodeSeq.cljs$lang$type = true;
cljs.core.ArrayNodeSeq.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/ArrayNodeSeq");
});
cljs.core.ArrayNodeSeq.prototype.cljs$core$IHash$_hash$arity$1 = (function (coll){
var this__9109 = this;
var h__2220__auto____9110 = this__9109.__hash;
if(!((h__2220__auto____9110 == null)))
{return h__2220__auto____9110;
} else
{var h__2220__auto____9111 = cljs.core.hash_coll.call(null,coll);
this__9109.__hash = h__2220__auto____9111;
return h__2220__auto____9111;
}
});
cljs.core.ArrayNodeSeq.prototype.cljs$core$ICollection$_conj$arity$2 = (function (coll,o){
var this__9112 = this;
return cljs.core.cons.call(null,o,coll);
});
cljs.core.ArrayNodeSeq.prototype.toString = (function (){
var this__9113 = this;
var this__9114 = this;
return cljs.core.pr_str.call(null,this__9114);
});
cljs.core.ArrayNodeSeq.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (this$){
var this__9115 = this;
return this$;
});
cljs.core.ArrayNodeSeq.prototype.cljs$core$ISeq$_first$arity$1 = (function (coll){
var this__9116 = this;
return cljs.core.first.call(null,this__9116.s);
});
cljs.core.ArrayNodeSeq.prototype.cljs$core$ISeq$_rest$arity$1 = (function (coll){
var this__9117 = this;
return cljs.core.create_array_node_seq.call(null,null,this__9117.nodes,this__9117.i,cljs.core.next.call(null,this__9117.s));
});
cljs.core.ArrayNodeSeq.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (coll,other){
var this__9118 = this;
return cljs.core.equiv_sequential.call(null,coll,other);
});
cljs.core.ArrayNodeSeq.prototype.cljs$core$IWithMeta$_with_meta$arity$2 = (function (coll,meta){
var this__9119 = this;
return (new cljs.core.ArrayNodeSeq(meta,this__9119.nodes,this__9119.i,this__9119.s,this__9119.__hash));
});
cljs.core.ArrayNodeSeq.prototype.cljs$core$IMeta$_meta$arity$1 = (function (coll){
var this__9120 = this;
return this__9120.meta;
});
cljs.core.ArrayNodeSeq.prototype.cljs$core$IEmptyableCollection$_empty$arity$1 = (function (coll){
var this__9121 = this;
return cljs.core.with_meta.call(null,cljs.core.List.EMPTY,this__9121.meta);
});
cljs.core.ArrayNodeSeq;
cljs.core.create_array_node_seq = (function() {
var create_array_node_seq = null;
var create_array_node_seq__1 = (function (nodes){
return create_array_node_seq.call(null,null,nodes,0,null);
});
var create_array_node_seq__4 = (function (meta,nodes,i,s){
if((s == null))
{var len__9128 = nodes.length;
var j__9129 = i;
while(true){
if((j__9129 < len__9128))
{var temp__3971__auto____9130 = (nodes[j__9129]);
if(cljs.core.truth_(temp__3971__auto____9130))
{var nj__9131 = temp__3971__auto____9130;
var temp__3971__auto____9132 = nj__9131.inode_seq();
if(cljs.core.truth_(temp__3971__auto____9132))
{var ns__9133 = temp__3971__auto____9132;
return (new cljs.core.ArrayNodeSeq(meta,nodes,(j__9129 + 1),ns__9133,null));
} else
{{
var G__9134 = (j__9129 + 1);
j__9129 = G__9134;
continue;
}
}
} else
{{
var G__9135 = (j__9129 + 1);
j__9129 = G__9135;
continue;
}
}
} else
{return null;
}
break;
}
} else
{return (new cljs.core.ArrayNodeSeq(meta,nodes,i,s,null));
}
});
create_array_node_seq = function(meta,nodes,i,s){
switch(arguments.length){
case 1:
return create_array_node_seq__1.call(this,meta);
case 4:
return create_array_node_seq__4.call(this,meta,nodes,i,s);
}
throw('Invalid arity: ' + arguments.length);
};
create_array_node_seq.cljs$lang$arity$1 = create_array_node_seq__1;
create_array_node_seq.cljs$lang$arity$4 = create_array_node_seq__4;
return create_array_node_seq;
})()
;

/**
* @constructor
*/
cljs.core.PersistentHashMap = (function (meta,cnt,root,has_nil_QMARK_,nil_val,__hash){
this.meta = meta;
this.cnt = cnt;
this.root = root;
this.has_nil_QMARK_ = has_nil_QMARK_;
this.nil_val = nil_val;
this.__hash = __hash;
this.cljs$lang$protocol_mask$partition1$ = 1;
this.cljs$lang$protocol_mask$partition0$ = 16123663;
})
cljs.core.PersistentHashMap.cljs$lang$type = true;
cljs.core.PersistentHashMap.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/PersistentHashMap");
});
cljs.core.PersistentHashMap.prototype.cljs$core$IEditableCollection$_as_transient$arity$1 = (function (coll){
var this__9138 = this;
return (new cljs.core.TransientHashMap({},this__9138.root,this__9138.cnt,this__9138.has_nil_QMARK_,this__9138.nil_val));
});
cljs.core.PersistentHashMap.prototype.cljs$core$IHash$_hash$arity$1 = (function (coll){
var this__9139 = this;
var h__2220__auto____9140 = this__9139.__hash;
if(!((h__2220__auto____9140 == null)))
{return h__2220__auto____9140;
} else
{var h__2220__auto____9141 = cljs.core.hash_imap.call(null,coll);
this__9139.__hash = h__2220__auto____9141;
return h__2220__auto____9141;
}
});
cljs.core.PersistentHashMap.prototype.cljs$core$ILookup$_lookup$arity$2 = (function (coll,k){
var this__9142 = this;
return coll.cljs$core$ILookup$_lookup$arity$3(coll,k,null);
});
cljs.core.PersistentHashMap.prototype.cljs$core$ILookup$_lookup$arity$3 = (function (coll,k,not_found){
var this__9143 = this;
if((k == null))
{if(this__9143.has_nil_QMARK_)
{return this__9143.nil_val;
} else
{return not_found;
}
} else
{if((this__9143.root == null))
{return not_found;
} else
{if("\uFDD0'else")
{return this__9143.root.inode_lookup(0,cljs.core.hash.call(null,k),k,not_found);
} else
{return null;
}
}
}
});
cljs.core.PersistentHashMap.prototype.cljs$core$IAssociative$_assoc$arity$3 = (function (coll,k,v){
var this__9144 = this;
if((k == null))
{if((function (){var and__3822__auto____9145 = this__9144.has_nil_QMARK_;
if(and__3822__auto____9145)
{return (v === this__9144.nil_val);
} else
{return and__3822__auto____9145;
}
})())
{return coll;
} else
{return (new cljs.core.PersistentHashMap(this__9144.meta,((this__9144.has_nil_QMARK_)?this__9144.cnt:(this__9144.cnt + 1)),this__9144.root,true,v,null));
}
} else
{var added_leaf_QMARK___9146 = (new cljs.core.Box(false));
var new_root__9147 = (((this__9144.root == null))?cljs.core.BitmapIndexedNode.EMPTY:this__9144.root).inode_assoc(0,cljs.core.hash.call(null,k),k,v,added_leaf_QMARK___9146);
if((new_root__9147 === this__9144.root))
{return coll;
} else
{return (new cljs.core.PersistentHashMap(this__9144.meta,((added_leaf_QMARK___9146.val)?(this__9144.cnt + 1):this__9144.cnt),new_root__9147,this__9144.has_nil_QMARK_,this__9144.nil_val,null));
}
}
});
cljs.core.PersistentHashMap.prototype.cljs$core$IAssociative$_contains_key_QMARK_$arity$2 = (function (coll,k){
var this__9148 = this;
if((k == null))
{return this__9148.has_nil_QMARK_;
} else
{if((this__9148.root == null))
{return false;
} else
{if("\uFDD0'else")
{return !((this__9148.root.inode_lookup(0,cljs.core.hash.call(null,k),k,cljs.core.lookup_sentinel) === cljs.core.lookup_sentinel));
} else
{return null;
}
}
}
});
cljs.core.PersistentHashMap.prototype.call = (function() {
var G__9171 = null;
var G__9171__2 = (function (this_sym9149,k){
var this__9151 = this;
var this_sym9149__9152 = this;
var coll__9153 = this_sym9149__9152;
return coll__9153.cljs$core$ILookup$_lookup$arity$2(coll__9153,k);
});
var G__9171__3 = (function (this_sym9150,k,not_found){
var this__9151 = this;
var this_sym9150__9154 = this;
var coll__9155 = this_sym9150__9154;
return coll__9155.cljs$core$ILookup$_lookup$arity$3(coll__9155,k,not_found);
});
G__9171 = function(this_sym9150,k,not_found){
switch(arguments.length){
case 2:
return G__9171__2.call(this,this_sym9150,k);
case 3:
return G__9171__3.call(this,this_sym9150,k,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
return G__9171;
})()
;
cljs.core.PersistentHashMap.prototype.apply = (function (this_sym9136,args9137){
var this__9156 = this;
return this_sym9136.call.apply(this_sym9136,[this_sym9136].concat(args9137.slice()));
});
cljs.core.PersistentHashMap.prototype.cljs$core$IKVReduce$_kv_reduce$arity$3 = (function (coll,f,init){
var this__9157 = this;
var init__9158 = ((this__9157.has_nil_QMARK_)?f.call(null,init,null,this__9157.nil_val):init);
if(cljs.core.reduced_QMARK_.call(null,init__9158))
{return cljs.core.deref.call(null,init__9158);
} else
{if(!((this__9157.root == null)))
{return this__9157.root.kv_reduce(f,init__9158);
} else
{if("\uFDD0'else")
{return init__9158;
} else
{return null;
}
}
}
});
cljs.core.PersistentHashMap.prototype.cljs$core$ICollection$_conj$arity$2 = (function (coll,entry){
var this__9159 = this;
if(cljs.core.vector_QMARK_.call(null,entry))
{return coll.cljs$core$IAssociative$_assoc$arity$3(coll,cljs.core._nth.call(null,entry,0),cljs.core._nth.call(null,entry,1));
} else
{return cljs.core.reduce.call(null,cljs.core._conj,coll,entry);
}
});
cljs.core.PersistentHashMap.prototype.toString = (function (){
var this__9160 = this;
var this__9161 = this;
return cljs.core.pr_str.call(null,this__9161);
});
cljs.core.PersistentHashMap.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (coll){
var this__9162 = this;
if((this__9162.cnt > 0))
{var s__9163 = ((!((this__9162.root == null)))?this__9162.root.inode_seq():null);
if(this__9162.has_nil_QMARK_)
{return cljs.core.cons.call(null,cljs.core.PersistentVector.fromArray([null,this__9162.nil_val], true),s__9163);
} else
{return s__9163;
}
} else
{return null;
}
});
cljs.core.PersistentHashMap.prototype.cljs$core$ICounted$_count$arity$1 = (function (coll){
var this__9164 = this;
return this__9164.cnt;
});
cljs.core.PersistentHashMap.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (coll,other){
var this__9165 = this;
return cljs.core.equiv_map.call(null,coll,other);
});
cljs.core.PersistentHashMap.prototype.cljs$core$IWithMeta$_with_meta$arity$2 = (function (coll,meta){
var this__9166 = this;
return (new cljs.core.PersistentHashMap(meta,this__9166.cnt,this__9166.root,this__9166.has_nil_QMARK_,this__9166.nil_val,this__9166.__hash));
});
cljs.core.PersistentHashMap.prototype.cljs$core$IMeta$_meta$arity$1 = (function (coll){
var this__9167 = this;
return this__9167.meta;
});
cljs.core.PersistentHashMap.prototype.cljs$core$IEmptyableCollection$_empty$arity$1 = (function (coll){
var this__9168 = this;
return cljs.core._with_meta.call(null,cljs.core.PersistentHashMap.EMPTY,this__9168.meta);
});
cljs.core.PersistentHashMap.prototype.cljs$core$IMap$_dissoc$arity$2 = (function (coll,k){
var this__9169 = this;
if((k == null))
{if(this__9169.has_nil_QMARK_)
{return (new cljs.core.PersistentHashMap(this__9169.meta,(this__9169.cnt - 1),this__9169.root,false,null,null));
} else
{return coll;
}
} else
{if((this__9169.root == null))
{return coll;
} else
{if("\uFDD0'else")
{var new_root__9170 = this__9169.root.inode_without(0,cljs.core.hash.call(null,k),k);
if((new_root__9170 === this__9169.root))
{return coll;
} else
{return (new cljs.core.PersistentHashMap(this__9169.meta,(this__9169.cnt - 1),new_root__9170,this__9169.has_nil_QMARK_,this__9169.nil_val,null));
}
} else
{return null;
}
}
}
});
cljs.core.PersistentHashMap;
cljs.core.PersistentHashMap.EMPTY = (new cljs.core.PersistentHashMap(null,0,null,false,null,0));
cljs.core.PersistentHashMap.fromArrays = (function (ks,vs){
var len__9172 = ks.length;
var i__9173 = 0;
var out__9174 = cljs.core.transient$.call(null,cljs.core.PersistentHashMap.EMPTY);
while(true){
if((i__9173 < len__9172))
{{
var G__9175 = (i__9173 + 1);
var G__9176 = cljs.core.assoc_BANG_.call(null,out__9174,(ks[i__9173]),(vs[i__9173]));
i__9173 = G__9175;
out__9174 = G__9176;
continue;
}
} else
{return cljs.core.persistent_BANG_.call(null,out__9174);
}
break;
}
});

/**
* @constructor
*/
cljs.core.TransientHashMap = (function (edit,root,count,has_nil_QMARK_,nil_val){
this.edit = edit;
this.root = root;
this.count = count;
this.has_nil_QMARK_ = has_nil_QMARK_;
this.nil_val = nil_val;
this.cljs$lang$protocol_mask$partition1$ = 14;
this.cljs$lang$protocol_mask$partition0$ = 258;
})
cljs.core.TransientHashMap.cljs$lang$type = true;
cljs.core.TransientHashMap.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/TransientHashMap");
});
cljs.core.TransientHashMap.prototype.cljs$core$ITransientMap$_dissoc_BANG_$arity$2 = (function (tcoll,key){
var this__9177 = this;
return tcoll.without_BANG_(key);
});
cljs.core.TransientHashMap.prototype.cljs$core$ITransientAssociative$_assoc_BANG_$arity$3 = (function (tcoll,key,val){
var this__9178 = this;
return tcoll.assoc_BANG_(key,val);
});
cljs.core.TransientHashMap.prototype.cljs$core$ITransientCollection$_conj_BANG_$arity$2 = (function (tcoll,val){
var this__9179 = this;
return tcoll.conj_BANG_(val);
});
cljs.core.TransientHashMap.prototype.cljs$core$ITransientCollection$_persistent_BANG_$arity$1 = (function (tcoll){
var this__9180 = this;
return tcoll.persistent_BANG_();
});
cljs.core.TransientHashMap.prototype.cljs$core$ILookup$_lookup$arity$2 = (function (tcoll,k){
var this__9181 = this;
if((k == null))
{if(this__9181.has_nil_QMARK_)
{return this__9181.nil_val;
} else
{return null;
}
} else
{if((this__9181.root == null))
{return null;
} else
{return this__9181.root.inode_lookup(0,cljs.core.hash.call(null,k),k);
}
}
});
cljs.core.TransientHashMap.prototype.cljs$core$ILookup$_lookup$arity$3 = (function (tcoll,k,not_found){
var this__9182 = this;
if((k == null))
{if(this__9182.has_nil_QMARK_)
{return this__9182.nil_val;
} else
{return not_found;
}
} else
{if((this__9182.root == null))
{return not_found;
} else
{return this__9182.root.inode_lookup(0,cljs.core.hash.call(null,k),k,not_found);
}
}
});
cljs.core.TransientHashMap.prototype.cljs$core$ICounted$_count$arity$1 = (function (coll){
var this__9183 = this;
if(this__9183.edit)
{return this__9183.count;
} else
{throw (new Error("count after persistent!"));
}
});
cljs.core.TransientHashMap.prototype.conj_BANG_ = (function (o){
var this__9184 = this;
var tcoll__9185 = this;
if(this__9184.edit)
{if((function (){var G__9186__9187 = o;
if(G__9186__9187)
{if((function (){var or__3824__auto____9188 = (G__9186__9187.cljs$lang$protocol_mask$partition0$ & 2048);
if(or__3824__auto____9188)
{return or__3824__auto____9188;
} else
{return G__9186__9187.cljs$core$IMapEntry$;
}
})())
{return true;
} else
{if((!G__9186__9187.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.IMapEntry,G__9186__9187);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.IMapEntry,G__9186__9187);
}
})())
{return tcoll__9185.assoc_BANG_(cljs.core.key.call(null,o),cljs.core.val.call(null,o));
} else
{var es__9189 = cljs.core.seq.call(null,o);
var tcoll__9190 = tcoll__9185;
while(true){
var temp__3971__auto____9191 = cljs.core.first.call(null,es__9189);
if(cljs.core.truth_(temp__3971__auto____9191))
{var e__9192 = temp__3971__auto____9191;
{
var G__9203 = cljs.core.next.call(null,es__9189);
var G__9204 = tcoll__9190.assoc_BANG_(cljs.core.key.call(null,e__9192),cljs.core.val.call(null,e__9192));
es__9189 = G__9203;
tcoll__9190 = G__9204;
continue;
}
} else
{return tcoll__9190;
}
break;
}
}
} else
{throw (new Error("conj! after persistent"));
}
});
cljs.core.TransientHashMap.prototype.assoc_BANG_ = (function (k,v){
var this__9193 = this;
var tcoll__9194 = this;
if(this__9193.edit)
{if((k == null))
{if((this__9193.nil_val === v))
{} else
{this__9193.nil_val = v;
}
if(this__9193.has_nil_QMARK_)
{} else
{this__9193.count = (this__9193.count + 1);
this__9193.has_nil_QMARK_ = true;
}
return tcoll__9194;
} else
{var added_leaf_QMARK___9195 = (new cljs.core.Box(false));
var node__9196 = (((this__9193.root == null))?cljs.core.BitmapIndexedNode.EMPTY:this__9193.root).inode_assoc_BANG_(this__9193.edit,0,cljs.core.hash.call(null,k),k,v,added_leaf_QMARK___9195);
if((node__9196 === this__9193.root))
{} else
{this__9193.root = node__9196;
}
if(added_leaf_QMARK___9195.val)
{this__9193.count = (this__9193.count + 1);
} else
{}
return tcoll__9194;
}
} else
{throw (new Error("assoc! after persistent!"));
}
});
cljs.core.TransientHashMap.prototype.without_BANG_ = (function (k){
var this__9197 = this;
var tcoll__9198 = this;
if(this__9197.edit)
{if((k == null))
{if(this__9197.has_nil_QMARK_)
{this__9197.has_nil_QMARK_ = false;
this__9197.nil_val = null;
this__9197.count = (this__9197.count - 1);
return tcoll__9198;
} else
{return tcoll__9198;
}
} else
{if((this__9197.root == null))
{return tcoll__9198;
} else
{var removed_leaf_QMARK___9199 = (new cljs.core.Box(false));
var node__9200 = this__9197.root.inode_without_BANG_(this__9197.edit,0,cljs.core.hash.call(null,k),k,removed_leaf_QMARK___9199);
if((node__9200 === this__9197.root))
{} else
{this__9197.root = node__9200;
}
if(cljs.core.truth_((removed_leaf_QMARK___9199[0])))
{this__9197.count = (this__9197.count - 1);
} else
{}
return tcoll__9198;
}
}
} else
{throw (new Error("dissoc! after persistent!"));
}
});
cljs.core.TransientHashMap.prototype.persistent_BANG_ = (function (){
var this__9201 = this;
var tcoll__9202 = this;
if(this__9201.edit)
{this__9201.edit = null;
return (new cljs.core.PersistentHashMap(null,this__9201.count,this__9201.root,this__9201.has_nil_QMARK_,this__9201.nil_val,null));
} else
{throw (new Error("persistent! called twice"));
}
});
cljs.core.TransientHashMap;
cljs.core.tree_map_seq_push = (function tree_map_seq_push(node,stack,ascending_QMARK_){
var t__9207 = node;
var stack__9208 = stack;
while(true){
if(!((t__9207 == null)))
{{
var G__9209 = ((ascending_QMARK_)?t__9207.left:t__9207.right);
var G__9210 = cljs.core.conj.call(null,stack__9208,t__9207);
t__9207 = G__9209;
stack__9208 = G__9210;
continue;
}
} else
{return stack__9208;
}
break;
}
});

/**
* @constructor
*/
cljs.core.PersistentTreeMapSeq = (function (meta,stack,ascending_QMARK_,cnt,__hash){
this.meta = meta;
this.stack = stack;
this.ascending_QMARK_ = ascending_QMARK_;
this.cnt = cnt;
this.__hash = __hash;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 31850570;
})
cljs.core.PersistentTreeMapSeq.cljs$lang$type = true;
cljs.core.PersistentTreeMapSeq.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/PersistentTreeMapSeq");
});
cljs.core.PersistentTreeMapSeq.prototype.cljs$core$IHash$_hash$arity$1 = (function (coll){
var this__9211 = this;
var h__2220__auto____9212 = this__9211.__hash;
if(!((h__2220__auto____9212 == null)))
{return h__2220__auto____9212;
} else
{var h__2220__auto____9213 = cljs.core.hash_coll.call(null,coll);
this__9211.__hash = h__2220__auto____9213;
return h__2220__auto____9213;
}
});
cljs.core.PersistentTreeMapSeq.prototype.cljs$core$ICollection$_conj$arity$2 = (function (coll,o){
var this__9214 = this;
return cljs.core.cons.call(null,o,coll);
});
cljs.core.PersistentTreeMapSeq.prototype.toString = (function (){
var this__9215 = this;
var this__9216 = this;
return cljs.core.pr_str.call(null,this__9216);
});
cljs.core.PersistentTreeMapSeq.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (this$){
var this__9217 = this;
return this$;
});
cljs.core.PersistentTreeMapSeq.prototype.cljs$core$ICounted$_count$arity$1 = (function (coll){
var this__9218 = this;
if((this__9218.cnt < 0))
{return (cljs.core.count.call(null,cljs.core.next.call(null,coll)) + 1);
} else
{return this__9218.cnt;
}
});
cljs.core.PersistentTreeMapSeq.prototype.cljs$core$ISeq$_first$arity$1 = (function (this$){
var this__9219 = this;
return cljs.core.peek.call(null,this__9219.stack);
});
cljs.core.PersistentTreeMapSeq.prototype.cljs$core$ISeq$_rest$arity$1 = (function (this$){
var this__9220 = this;
var t__9221 = cljs.core.first.call(null,this__9220.stack);
var next_stack__9222 = cljs.core.tree_map_seq_push.call(null,((this__9220.ascending_QMARK_)?t__9221.right:t__9221.left),cljs.core.next.call(null,this__9220.stack),this__9220.ascending_QMARK_);
if(!((next_stack__9222 == null)))
{return (new cljs.core.PersistentTreeMapSeq(null,next_stack__9222,this__9220.ascending_QMARK_,(this__9220.cnt - 1),null));
} else
{return cljs.core.List.EMPTY;
}
});
cljs.core.PersistentTreeMapSeq.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (coll,other){
var this__9223 = this;
return cljs.core.equiv_sequential.call(null,coll,other);
});
cljs.core.PersistentTreeMapSeq.prototype.cljs$core$IWithMeta$_with_meta$arity$2 = (function (coll,meta){
var this__9224 = this;
return (new cljs.core.PersistentTreeMapSeq(meta,this__9224.stack,this__9224.ascending_QMARK_,this__9224.cnt,this__9224.__hash));
});
cljs.core.PersistentTreeMapSeq.prototype.cljs$core$IMeta$_meta$arity$1 = (function (coll){
var this__9225 = this;
return this__9225.meta;
});
cljs.core.PersistentTreeMapSeq;
cljs.core.create_tree_map_seq = (function create_tree_map_seq(tree,ascending_QMARK_,cnt){
return (new cljs.core.PersistentTreeMapSeq(null,cljs.core.tree_map_seq_push.call(null,tree,null,ascending_QMARK_),ascending_QMARK_,cnt,null));
});
cljs.core.balance_left = (function balance_left(key,val,ins,right){
if(cljs.core.instance_QMARK_.call(null,cljs.core.RedNode,ins))
{if(cljs.core.instance_QMARK_.call(null,cljs.core.RedNode,ins.left))
{return (new cljs.core.RedNode(ins.key,ins.val,ins.left.blacken(),(new cljs.core.BlackNode(key,val,ins.right,right,null)),null));
} else
{if(cljs.core.instance_QMARK_.call(null,cljs.core.RedNode,ins.right))
{return (new cljs.core.RedNode(ins.right.key,ins.right.val,(new cljs.core.BlackNode(ins.key,ins.val,ins.left,ins.right.left,null)),(new cljs.core.BlackNode(key,val,ins.right.right,right,null)),null));
} else
{if("\uFDD0'else")
{return (new cljs.core.BlackNode(key,val,ins,right,null));
} else
{return null;
}
}
}
} else
{return (new cljs.core.BlackNode(key,val,ins,right,null));
}
});
cljs.core.balance_right = (function balance_right(key,val,left,ins){
if(cljs.core.instance_QMARK_.call(null,cljs.core.RedNode,ins))
{if(cljs.core.instance_QMARK_.call(null,cljs.core.RedNode,ins.right))
{return (new cljs.core.RedNode(ins.key,ins.val,(new cljs.core.BlackNode(key,val,left,ins.left,null)),ins.right.blacken(),null));
} else
{if(cljs.core.instance_QMARK_.call(null,cljs.core.RedNode,ins.left))
{return (new cljs.core.RedNode(ins.left.key,ins.left.val,(new cljs.core.BlackNode(key,val,left,ins.left.left,null)),(new cljs.core.BlackNode(ins.key,ins.val,ins.left.right,ins.right,null)),null));
} else
{if("\uFDD0'else")
{return (new cljs.core.BlackNode(key,val,left,ins,null));
} else
{return null;
}
}
}
} else
{return (new cljs.core.BlackNode(key,val,left,ins,null));
}
});
cljs.core.balance_left_del = (function balance_left_del(key,val,del,right){
if(cljs.core.instance_QMARK_.call(null,cljs.core.RedNode,del))
{return (new cljs.core.RedNode(key,val,del.blacken(),right,null));
} else
{if(cljs.core.instance_QMARK_.call(null,cljs.core.BlackNode,right))
{return cljs.core.balance_right.call(null,key,val,del,right.redden());
} else
{if((function (){var and__3822__auto____9227 = cljs.core.instance_QMARK_.call(null,cljs.core.RedNode,right);
if(and__3822__auto____9227)
{return cljs.core.instance_QMARK_.call(null,cljs.core.BlackNode,right.left);
} else
{return and__3822__auto____9227;
}
})())
{return (new cljs.core.RedNode(right.left.key,right.left.val,(new cljs.core.BlackNode(key,val,del,right.left.left,null)),cljs.core.balance_right.call(null,right.key,right.val,right.left.right,right.right.redden()),null));
} else
{if("\uFDD0'else")
{throw (new Error("red-black tree invariant violation"));
} else
{return null;
}
}
}
}
});
cljs.core.balance_right_del = (function balance_right_del(key,val,left,del){
if(cljs.core.instance_QMARK_.call(null,cljs.core.RedNode,del))
{return (new cljs.core.RedNode(key,val,left,del.blacken(),null));
} else
{if(cljs.core.instance_QMARK_.call(null,cljs.core.BlackNode,left))
{return cljs.core.balance_left.call(null,key,val,left.redden(),del);
} else
{if((function (){var and__3822__auto____9229 = cljs.core.instance_QMARK_.call(null,cljs.core.RedNode,left);
if(and__3822__auto____9229)
{return cljs.core.instance_QMARK_.call(null,cljs.core.BlackNode,left.right);
} else
{return and__3822__auto____9229;
}
})())
{return (new cljs.core.RedNode(left.right.key,left.right.val,cljs.core.balance_left.call(null,left.key,left.val,left.left.redden(),left.right.left),(new cljs.core.BlackNode(key,val,left.right.right,del,null)),null));
} else
{if("\uFDD0'else")
{throw (new Error("red-black tree invariant violation"));
} else
{return null;
}
}
}
}
});
cljs.core.tree_map_kv_reduce = (function tree_map_kv_reduce(node,f,init){
var init__9233 = f.call(null,init,node.key,node.val);
if(cljs.core.reduced_QMARK_.call(null,init__9233))
{return cljs.core.deref.call(null,init__9233);
} else
{var init__9234 = ((!((node.left == null)))?tree_map_kv_reduce.call(null,node.left,f,init__9233):init__9233);
if(cljs.core.reduced_QMARK_.call(null,init__9234))
{return cljs.core.deref.call(null,init__9234);
} else
{var init__9235 = ((!((node.right == null)))?tree_map_kv_reduce.call(null,node.right,f,init__9234):init__9234);
if(cljs.core.reduced_QMARK_.call(null,init__9235))
{return cljs.core.deref.call(null,init__9235);
} else
{return init__9235;
}
}
}
});

/**
* @constructor
*/
cljs.core.BlackNode = (function (key,val,left,right,__hash){
this.key = key;
this.val = val;
this.left = left;
this.right = right;
this.__hash = __hash;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 32402207;
})
cljs.core.BlackNode.cljs$lang$type = true;
cljs.core.BlackNode.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/BlackNode");
});
cljs.core.BlackNode.prototype.cljs$core$IHash$_hash$arity$1 = (function (coll){
var this__9238 = this;
var h__2220__auto____9239 = this__9238.__hash;
if(!((h__2220__auto____9239 == null)))
{return h__2220__auto____9239;
} else
{var h__2220__auto____9240 = cljs.core.hash_coll.call(null,coll);
this__9238.__hash = h__2220__auto____9240;
return h__2220__auto____9240;
}
});
cljs.core.BlackNode.prototype.cljs$core$ILookup$_lookup$arity$2 = (function (node,k){
var this__9241 = this;
return node.cljs$core$IIndexed$_nth$arity$3(node,k,null);
});
cljs.core.BlackNode.prototype.cljs$core$ILookup$_lookup$arity$3 = (function (node,k,not_found){
var this__9242 = this;
return node.cljs$core$IIndexed$_nth$arity$3(node,k,not_found);
});
cljs.core.BlackNode.prototype.cljs$core$IAssociative$_assoc$arity$3 = (function (node,k,v){
var this__9243 = this;
return cljs.core.assoc.call(null,cljs.core.PersistentVector.fromArray([this__9243.key,this__9243.val], true),k,v);
});
cljs.core.BlackNode.prototype.call = (function() {
var G__9291 = null;
var G__9291__2 = (function (this_sym9244,k){
var this__9246 = this;
var this_sym9244__9247 = this;
var node__9248 = this_sym9244__9247;
return node__9248.cljs$core$ILookup$_lookup$arity$2(node__9248,k);
});
var G__9291__3 = (function (this_sym9245,k,not_found){
var this__9246 = this;
var this_sym9245__9249 = this;
var node__9250 = this_sym9245__9249;
return node__9250.cljs$core$ILookup$_lookup$arity$3(node__9250,k,not_found);
});
G__9291 = function(this_sym9245,k,not_found){
switch(arguments.length){
case 2:
return G__9291__2.call(this,this_sym9245,k);
case 3:
return G__9291__3.call(this,this_sym9245,k,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
return G__9291;
})()
;
cljs.core.BlackNode.prototype.apply = (function (this_sym9236,args9237){
var this__9251 = this;
return this_sym9236.call.apply(this_sym9236,[this_sym9236].concat(args9237.slice()));
});
cljs.core.BlackNode.prototype.cljs$core$ICollection$_conj$arity$2 = (function (node,o){
var this__9252 = this;
return cljs.core.PersistentVector.fromArray([this__9252.key,this__9252.val,o], true);
});
cljs.core.BlackNode.prototype.cljs$core$IMapEntry$_key$arity$1 = (function (node){
var this__9253 = this;
return this__9253.key;
});
cljs.core.BlackNode.prototype.cljs$core$IMapEntry$_val$arity$1 = (function (node){
var this__9254 = this;
return this__9254.val;
});
cljs.core.BlackNode.prototype.add_right = (function (ins){
var this__9255 = this;
var node__9256 = this;
return ins.balance_right(node__9256);
});
cljs.core.BlackNode.prototype.redden = (function (){
var this__9257 = this;
var node__9258 = this;
return (new cljs.core.RedNode(this__9257.key,this__9257.val,this__9257.left,this__9257.right,null));
});
cljs.core.BlackNode.prototype.remove_right = (function (del){
var this__9259 = this;
var node__9260 = this;
return cljs.core.balance_right_del.call(null,this__9259.key,this__9259.val,this__9259.left,del);
});
cljs.core.BlackNode.prototype.replace = (function (key,val,left,right){
var this__9261 = this;
var node__9262 = this;
return (new cljs.core.BlackNode(key,val,left,right,null));
});
cljs.core.BlackNode.prototype.kv_reduce = (function (f,init){
var this__9263 = this;
var node__9264 = this;
return cljs.core.tree_map_kv_reduce.call(null,node__9264,f,init);
});
cljs.core.BlackNode.prototype.remove_left = (function (del){
var this__9265 = this;
var node__9266 = this;
return cljs.core.balance_left_del.call(null,this__9265.key,this__9265.val,del,this__9265.right);
});
cljs.core.BlackNode.prototype.add_left = (function (ins){
var this__9267 = this;
var node__9268 = this;
return ins.balance_left(node__9268);
});
cljs.core.BlackNode.prototype.balance_left = (function (parent){
var this__9269 = this;
var node__9270 = this;
return (new cljs.core.BlackNode(parent.key,parent.val,node__9270,parent.right,null));
});
cljs.core.BlackNode.prototype.toString = (function() {
var G__9292 = null;
var G__9292__0 = (function (){
var this__9271 = this;
var this__9273 = this;
return cljs.core.pr_str.call(null,this__9273);
});
G__9292 = function(){
switch(arguments.length){
case 0:
return G__9292__0.call(this);
}
throw('Invalid arity: ' + arguments.length);
};
return G__9292;
})()
;
cljs.core.BlackNode.prototype.balance_right = (function (parent){
var this__9274 = this;
var node__9275 = this;
return (new cljs.core.BlackNode(parent.key,parent.val,parent.left,node__9275,null));
});
cljs.core.BlackNode.prototype.blacken = (function (){
var this__9276 = this;
var node__9277 = this;
return node__9277;
});
cljs.core.BlackNode.prototype.cljs$core$IReduce$_reduce$arity$2 = (function (node,f){
var this__9278 = this;
return cljs.core.ci_reduce.call(null,node,f);
});
cljs.core.BlackNode.prototype.cljs$core$IReduce$_reduce$arity$3 = (function (node,f,start){
var this__9279 = this;
return cljs.core.ci_reduce.call(null,node,f,start);
});
cljs.core.BlackNode.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (node){
var this__9280 = this;
return cljs.core.list.call(null,this__9280.key,this__9280.val);
});
cljs.core.BlackNode.prototype.cljs$core$ICounted$_count$arity$1 = (function (node){
var this__9281 = this;
return 2;
});
cljs.core.BlackNode.prototype.cljs$core$IStack$_peek$arity$1 = (function (node){
var this__9282 = this;
return this__9282.val;
});
cljs.core.BlackNode.prototype.cljs$core$IStack$_pop$arity$1 = (function (node){
var this__9283 = this;
return cljs.core.PersistentVector.fromArray([this__9283.key], true);
});
cljs.core.BlackNode.prototype.cljs$core$IVector$_assoc_n$arity$3 = (function (node,n,v){
var this__9284 = this;
return cljs.core._assoc_n.call(null,cljs.core.PersistentVector.fromArray([this__9284.key,this__9284.val], true),n,v);
});
cljs.core.BlackNode.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (coll,other){
var this__9285 = this;
return cljs.core.equiv_sequential.call(null,coll,other);
});
cljs.core.BlackNode.prototype.cljs$core$IWithMeta$_with_meta$arity$2 = (function (node,meta){
var this__9286 = this;
return cljs.core.with_meta.call(null,cljs.core.PersistentVector.fromArray([this__9286.key,this__9286.val], true),meta);
});
cljs.core.BlackNode.prototype.cljs$core$IMeta$_meta$arity$1 = (function (node){
var this__9287 = this;
return null;
});
cljs.core.BlackNode.prototype.cljs$core$IIndexed$_nth$arity$2 = (function (node,n){
var this__9288 = this;
if((n === 0))
{return this__9288.key;
} else
{if((n === 1))
{return this__9288.val;
} else
{if("\uFDD0'else")
{return null;
} else
{return null;
}
}
}
});
cljs.core.BlackNode.prototype.cljs$core$IIndexed$_nth$arity$3 = (function (node,n,not_found){
var this__9289 = this;
if((n === 0))
{return this__9289.key;
} else
{if((n === 1))
{return this__9289.val;
} else
{if("\uFDD0'else")
{return not_found;
} else
{return null;
}
}
}
});
cljs.core.BlackNode.prototype.cljs$core$IEmptyableCollection$_empty$arity$1 = (function (node){
var this__9290 = this;
return cljs.core.PersistentVector.EMPTY;
});
cljs.core.BlackNode;

/**
* @constructor
*/
cljs.core.RedNode = (function (key,val,left,right,__hash){
this.key = key;
this.val = val;
this.left = left;
this.right = right;
this.__hash = __hash;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 32402207;
})
cljs.core.RedNode.cljs$lang$type = true;
cljs.core.RedNode.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/RedNode");
});
cljs.core.RedNode.prototype.cljs$core$IHash$_hash$arity$1 = (function (coll){
var this__9295 = this;
var h__2220__auto____9296 = this__9295.__hash;
if(!((h__2220__auto____9296 == null)))
{return h__2220__auto____9296;
} else
{var h__2220__auto____9297 = cljs.core.hash_coll.call(null,coll);
this__9295.__hash = h__2220__auto____9297;
return h__2220__auto____9297;
}
});
cljs.core.RedNode.prototype.cljs$core$ILookup$_lookup$arity$2 = (function (node,k){
var this__9298 = this;
return node.cljs$core$IIndexed$_nth$arity$3(node,k,null);
});
cljs.core.RedNode.prototype.cljs$core$ILookup$_lookup$arity$3 = (function (node,k,not_found){
var this__9299 = this;
return node.cljs$core$IIndexed$_nth$arity$3(node,k,not_found);
});
cljs.core.RedNode.prototype.cljs$core$IAssociative$_assoc$arity$3 = (function (node,k,v){
var this__9300 = this;
return cljs.core.assoc.call(null,cljs.core.PersistentVector.fromArray([this__9300.key,this__9300.val], true),k,v);
});
cljs.core.RedNode.prototype.call = (function() {
var G__9348 = null;
var G__9348__2 = (function (this_sym9301,k){
var this__9303 = this;
var this_sym9301__9304 = this;
var node__9305 = this_sym9301__9304;
return node__9305.cljs$core$ILookup$_lookup$arity$2(node__9305,k);
});
var G__9348__3 = (function (this_sym9302,k,not_found){
var this__9303 = this;
var this_sym9302__9306 = this;
var node__9307 = this_sym9302__9306;
return node__9307.cljs$core$ILookup$_lookup$arity$3(node__9307,k,not_found);
});
G__9348 = function(this_sym9302,k,not_found){
switch(arguments.length){
case 2:
return G__9348__2.call(this,this_sym9302,k);
case 3:
return G__9348__3.call(this,this_sym9302,k,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
return G__9348;
})()
;
cljs.core.RedNode.prototype.apply = (function (this_sym9293,args9294){
var this__9308 = this;
return this_sym9293.call.apply(this_sym9293,[this_sym9293].concat(args9294.slice()));
});
cljs.core.RedNode.prototype.cljs$core$ICollection$_conj$arity$2 = (function (node,o){
var this__9309 = this;
return cljs.core.PersistentVector.fromArray([this__9309.key,this__9309.val,o], true);
});
cljs.core.RedNode.prototype.cljs$core$IMapEntry$_key$arity$1 = (function (node){
var this__9310 = this;
return this__9310.key;
});
cljs.core.RedNode.prototype.cljs$core$IMapEntry$_val$arity$1 = (function (node){
var this__9311 = this;
return this__9311.val;
});
cljs.core.RedNode.prototype.add_right = (function (ins){
var this__9312 = this;
var node__9313 = this;
return (new cljs.core.RedNode(this__9312.key,this__9312.val,this__9312.left,ins,null));
});
cljs.core.RedNode.prototype.redden = (function (){
var this__9314 = this;
var node__9315 = this;
throw (new Error("red-black tree invariant violation"));
});
cljs.core.RedNode.prototype.remove_right = (function (del){
var this__9316 = this;
var node__9317 = this;
return (new cljs.core.RedNode(this__9316.key,this__9316.val,this__9316.left,del,null));
});
cljs.core.RedNode.prototype.replace = (function (key,val,left,right){
var this__9318 = this;
var node__9319 = this;
return (new cljs.core.RedNode(key,val,left,right,null));
});
cljs.core.RedNode.prototype.kv_reduce = (function (f,init){
var this__9320 = this;
var node__9321 = this;
return cljs.core.tree_map_kv_reduce.call(null,node__9321,f,init);
});
cljs.core.RedNode.prototype.remove_left = (function (del){
var this__9322 = this;
var node__9323 = this;
return (new cljs.core.RedNode(this__9322.key,this__9322.val,del,this__9322.right,null));
});
cljs.core.RedNode.prototype.add_left = (function (ins){
var this__9324 = this;
var node__9325 = this;
return (new cljs.core.RedNode(this__9324.key,this__9324.val,ins,this__9324.right,null));
});
cljs.core.RedNode.prototype.balance_left = (function (parent){
var this__9326 = this;
var node__9327 = this;
if(cljs.core.instance_QMARK_.call(null,cljs.core.RedNode,this__9326.left))
{return (new cljs.core.RedNode(this__9326.key,this__9326.val,this__9326.left.blacken(),(new cljs.core.BlackNode(parent.key,parent.val,this__9326.right,parent.right,null)),null));
} else
{if(cljs.core.instance_QMARK_.call(null,cljs.core.RedNode,this__9326.right))
{return (new cljs.core.RedNode(this__9326.right.key,this__9326.right.val,(new cljs.core.BlackNode(this__9326.key,this__9326.val,this__9326.left,this__9326.right.left,null)),(new cljs.core.BlackNode(parent.key,parent.val,this__9326.right.right,parent.right,null)),null));
} else
{if("\uFDD0'else")
{return (new cljs.core.BlackNode(parent.key,parent.val,node__9327,parent.right,null));
} else
{return null;
}
}
}
});
cljs.core.RedNode.prototype.toString = (function() {
var G__9349 = null;
var G__9349__0 = (function (){
var this__9328 = this;
var this__9330 = this;
return cljs.core.pr_str.call(null,this__9330);
});
G__9349 = function(){
switch(arguments.length){
case 0:
return G__9349__0.call(this);
}
throw('Invalid arity: ' + arguments.length);
};
return G__9349;
})()
;
cljs.core.RedNode.prototype.balance_right = (function (parent){
var this__9331 = this;
var node__9332 = this;
if(cljs.core.instance_QMARK_.call(null,cljs.core.RedNode,this__9331.right))
{return (new cljs.core.RedNode(this__9331.key,this__9331.val,(new cljs.core.BlackNode(parent.key,parent.val,parent.left,this__9331.left,null)),this__9331.right.blacken(),null));
} else
{if(cljs.core.instance_QMARK_.call(null,cljs.core.RedNode,this__9331.left))
{return (new cljs.core.RedNode(this__9331.left.key,this__9331.left.val,(new cljs.core.BlackNode(parent.key,parent.val,parent.left,this__9331.left.left,null)),(new cljs.core.BlackNode(this__9331.key,this__9331.val,this__9331.left.right,this__9331.right,null)),null));
} else
{if("\uFDD0'else")
{return (new cljs.core.BlackNode(parent.key,parent.val,parent.left,node__9332,null));
} else
{return null;
}
}
}
});
cljs.core.RedNode.prototype.blacken = (function (){
var this__9333 = this;
var node__9334 = this;
return (new cljs.core.BlackNode(this__9333.key,this__9333.val,this__9333.left,this__9333.right,null));
});
cljs.core.RedNode.prototype.cljs$core$IReduce$_reduce$arity$2 = (function (node,f){
var this__9335 = this;
return cljs.core.ci_reduce.call(null,node,f);
});
cljs.core.RedNode.prototype.cljs$core$IReduce$_reduce$arity$3 = (function (node,f,start){
var this__9336 = this;
return cljs.core.ci_reduce.call(null,node,f,start);
});
cljs.core.RedNode.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (node){
var this__9337 = this;
return cljs.core.list.call(null,this__9337.key,this__9337.val);
});
cljs.core.RedNode.prototype.cljs$core$ICounted$_count$arity$1 = (function (node){
var this__9338 = this;
return 2;
});
cljs.core.RedNode.prototype.cljs$core$IStack$_peek$arity$1 = (function (node){
var this__9339 = this;
return this__9339.val;
});
cljs.core.RedNode.prototype.cljs$core$IStack$_pop$arity$1 = (function (node){
var this__9340 = this;
return cljs.core.PersistentVector.fromArray([this__9340.key], true);
});
cljs.core.RedNode.prototype.cljs$core$IVector$_assoc_n$arity$3 = (function (node,n,v){
var this__9341 = this;
return cljs.core._assoc_n.call(null,cljs.core.PersistentVector.fromArray([this__9341.key,this__9341.val], true),n,v);
});
cljs.core.RedNode.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (coll,other){
var this__9342 = this;
return cljs.core.equiv_sequential.call(null,coll,other);
});
cljs.core.RedNode.prototype.cljs$core$IWithMeta$_with_meta$arity$2 = (function (node,meta){
var this__9343 = this;
return cljs.core.with_meta.call(null,cljs.core.PersistentVector.fromArray([this__9343.key,this__9343.val], true),meta);
});
cljs.core.RedNode.prototype.cljs$core$IMeta$_meta$arity$1 = (function (node){
var this__9344 = this;
return null;
});
cljs.core.RedNode.prototype.cljs$core$IIndexed$_nth$arity$2 = (function (node,n){
var this__9345 = this;
if((n === 0))
{return this__9345.key;
} else
{if((n === 1))
{return this__9345.val;
} else
{if("\uFDD0'else")
{return null;
} else
{return null;
}
}
}
});
cljs.core.RedNode.prototype.cljs$core$IIndexed$_nth$arity$3 = (function (node,n,not_found){
var this__9346 = this;
if((n === 0))
{return this__9346.key;
} else
{if((n === 1))
{return this__9346.val;
} else
{if("\uFDD0'else")
{return not_found;
} else
{return null;
}
}
}
});
cljs.core.RedNode.prototype.cljs$core$IEmptyableCollection$_empty$arity$1 = (function (node){
var this__9347 = this;
return cljs.core.PersistentVector.EMPTY;
});
cljs.core.RedNode;
cljs.core.tree_map_add = (function tree_map_add(comp,tree,k,v,found){
if((tree == null))
{return (new cljs.core.RedNode(k,v,null,null,null));
} else
{var c__9353 = comp.call(null,k,tree.key);
if((c__9353 === 0))
{(found[0] = tree);
return null;
} else
{if((c__9353 < 0))
{var ins__9354 = tree_map_add.call(null,comp,tree.left,k,v,found);
if(!((ins__9354 == null)))
{return tree.add_left(ins__9354);
} else
{return null;
}
} else
{if("\uFDD0'else")
{var ins__9355 = tree_map_add.call(null,comp,tree.right,k,v,found);
if(!((ins__9355 == null)))
{return tree.add_right(ins__9355);
} else
{return null;
}
} else
{return null;
}
}
}
}
});
cljs.core.tree_map_append = (function tree_map_append(left,right){
if((left == null))
{return right;
} else
{if((right == null))
{return left;
} else
{if(cljs.core.instance_QMARK_.call(null,cljs.core.RedNode,left))
{if(cljs.core.instance_QMARK_.call(null,cljs.core.RedNode,right))
{var app__9358 = tree_map_append.call(null,left.right,right.left);
if(cljs.core.instance_QMARK_.call(null,cljs.core.RedNode,app__9358))
{return (new cljs.core.RedNode(app__9358.key,app__9358.val,(new cljs.core.RedNode(left.key,left.val,left.left,app__9358.left,null)),(new cljs.core.RedNode(right.key,right.val,app__9358.right,right.right,null)),null));
} else
{return (new cljs.core.RedNode(left.key,left.val,left.left,(new cljs.core.RedNode(right.key,right.val,app__9358,right.right,null)),null));
}
} else
{return (new cljs.core.RedNode(left.key,left.val,left.left,tree_map_append.call(null,left.right,right),null));
}
} else
{if(cljs.core.instance_QMARK_.call(null,cljs.core.RedNode,right))
{return (new cljs.core.RedNode(right.key,right.val,tree_map_append.call(null,left,right.left),right.right,null));
} else
{if("\uFDD0'else")
{var app__9359 = tree_map_append.call(null,left.right,right.left);
if(cljs.core.instance_QMARK_.call(null,cljs.core.RedNode,app__9359))
{return (new cljs.core.RedNode(app__9359.key,app__9359.val,(new cljs.core.BlackNode(left.key,left.val,left.left,app__9359.left,null)),(new cljs.core.BlackNode(right.key,right.val,app__9359.right,right.right,null)),null));
} else
{return cljs.core.balance_left_del.call(null,left.key,left.val,left.left,(new cljs.core.BlackNode(right.key,right.val,app__9359,right.right,null)));
}
} else
{return null;
}
}
}
}
}
});
cljs.core.tree_map_remove = (function tree_map_remove(comp,tree,k,found){
if(!((tree == null)))
{var c__9365 = comp.call(null,k,tree.key);
if((c__9365 === 0))
{(found[0] = tree);
return cljs.core.tree_map_append.call(null,tree.left,tree.right);
} else
{if((c__9365 < 0))
{var del__9366 = tree_map_remove.call(null,comp,tree.left,k,found);
if((function (){var or__3824__auto____9367 = !((del__9366 == null));
if(or__3824__auto____9367)
{return or__3824__auto____9367;
} else
{return !(((found[0]) == null));
}
})())
{if(cljs.core.instance_QMARK_.call(null,cljs.core.BlackNode,tree.left))
{return cljs.core.balance_left_del.call(null,tree.key,tree.val,del__9366,tree.right);
} else
{return (new cljs.core.RedNode(tree.key,tree.val,del__9366,tree.right,null));
}
} else
{return null;
}
} else
{if("\uFDD0'else")
{var del__9368 = tree_map_remove.call(null,comp,tree.right,k,found);
if((function (){var or__3824__auto____9369 = !((del__9368 == null));
if(or__3824__auto____9369)
{return or__3824__auto____9369;
} else
{return !(((found[0]) == null));
}
})())
{if(cljs.core.instance_QMARK_.call(null,cljs.core.BlackNode,tree.right))
{return cljs.core.balance_right_del.call(null,tree.key,tree.val,tree.left,del__9368);
} else
{return (new cljs.core.RedNode(tree.key,tree.val,tree.left,del__9368,null));
}
} else
{return null;
}
} else
{return null;
}
}
}
} else
{return null;
}
});
cljs.core.tree_map_replace = (function tree_map_replace(comp,tree,k,v){
var tk__9372 = tree.key;
var c__9373 = comp.call(null,k,tk__9372);
if((c__9373 === 0))
{return tree.replace(tk__9372,v,tree.left,tree.right);
} else
{if((c__9373 < 0))
{return tree.replace(tk__9372,tree.val,tree_map_replace.call(null,comp,tree.left,k,v),tree.right);
} else
{if("\uFDD0'else")
{return tree.replace(tk__9372,tree.val,tree.left,tree_map_replace.call(null,comp,tree.right,k,v));
} else
{return null;
}
}
}
});

/**
* @constructor
*/
cljs.core.PersistentTreeMap = (function (comp,tree,cnt,meta,__hash){
this.comp = comp;
this.tree = tree;
this.cnt = cnt;
this.meta = meta;
this.__hash = __hash;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 418776847;
})
cljs.core.PersistentTreeMap.cljs$lang$type = true;
cljs.core.PersistentTreeMap.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/PersistentTreeMap");
});
cljs.core.PersistentTreeMap.prototype.cljs$core$IHash$_hash$arity$1 = (function (coll){
var this__9376 = this;
var h__2220__auto____9377 = this__9376.__hash;
if(!((h__2220__auto____9377 == null)))
{return h__2220__auto____9377;
} else
{var h__2220__auto____9378 = cljs.core.hash_imap.call(null,coll);
this__9376.__hash = h__2220__auto____9378;
return h__2220__auto____9378;
}
});
cljs.core.PersistentTreeMap.prototype.cljs$core$ILookup$_lookup$arity$2 = (function (coll,k){
var this__9379 = this;
return coll.cljs$core$ILookup$_lookup$arity$3(coll,k,null);
});
cljs.core.PersistentTreeMap.prototype.cljs$core$ILookup$_lookup$arity$3 = (function (coll,k,not_found){
var this__9380 = this;
var n__9381 = coll.entry_at(k);
if(!((n__9381 == null)))
{return n__9381.val;
} else
{return not_found;
}
});
cljs.core.PersistentTreeMap.prototype.cljs$core$IAssociative$_assoc$arity$3 = (function (coll,k,v){
var this__9382 = this;
var found__9383 = [null];
var t__9384 = cljs.core.tree_map_add.call(null,this__9382.comp,this__9382.tree,k,v,found__9383);
if((t__9384 == null))
{var found_node__9385 = cljs.core.nth.call(null,found__9383,0);
if(cljs.core._EQ_.call(null,v,found_node__9385.val))
{return coll;
} else
{return (new cljs.core.PersistentTreeMap(this__9382.comp,cljs.core.tree_map_replace.call(null,this__9382.comp,this__9382.tree,k,v),this__9382.cnt,this__9382.meta,null));
}
} else
{return (new cljs.core.PersistentTreeMap(this__9382.comp,t__9384.blacken(),(this__9382.cnt + 1),this__9382.meta,null));
}
});
cljs.core.PersistentTreeMap.prototype.cljs$core$IAssociative$_contains_key_QMARK_$arity$2 = (function (coll,k){
var this__9386 = this;
return !((coll.entry_at(k) == null));
});
cljs.core.PersistentTreeMap.prototype.call = (function() {
var G__9420 = null;
var G__9420__2 = (function (this_sym9387,k){
var this__9389 = this;
var this_sym9387__9390 = this;
var coll__9391 = this_sym9387__9390;
return coll__9391.cljs$core$ILookup$_lookup$arity$2(coll__9391,k);
});
var G__9420__3 = (function (this_sym9388,k,not_found){
var this__9389 = this;
var this_sym9388__9392 = this;
var coll__9393 = this_sym9388__9392;
return coll__9393.cljs$core$ILookup$_lookup$arity$3(coll__9393,k,not_found);
});
G__9420 = function(this_sym9388,k,not_found){
switch(arguments.length){
case 2:
return G__9420__2.call(this,this_sym9388,k);
case 3:
return G__9420__3.call(this,this_sym9388,k,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
return G__9420;
})()
;
cljs.core.PersistentTreeMap.prototype.apply = (function (this_sym9374,args9375){
var this__9394 = this;
return this_sym9374.call.apply(this_sym9374,[this_sym9374].concat(args9375.slice()));
});
cljs.core.PersistentTreeMap.prototype.cljs$core$IKVReduce$_kv_reduce$arity$3 = (function (coll,f,init){
var this__9395 = this;
if(!((this__9395.tree == null)))
{return cljs.core.tree_map_kv_reduce.call(null,this__9395.tree,f,init);
} else
{return init;
}
});
cljs.core.PersistentTreeMap.prototype.cljs$core$ICollection$_conj$arity$2 = (function (coll,entry){
var this__9396 = this;
if(cljs.core.vector_QMARK_.call(null,entry))
{return coll.cljs$core$IAssociative$_assoc$arity$3(coll,cljs.core._nth.call(null,entry,0),cljs.core._nth.call(null,entry,1));
} else
{return cljs.core.reduce.call(null,cljs.core._conj,coll,entry);
}
});
cljs.core.PersistentTreeMap.prototype.cljs$core$IReversible$_rseq$arity$1 = (function (coll){
var this__9397 = this;
if((this__9397.cnt > 0))
{return cljs.core.create_tree_map_seq.call(null,this__9397.tree,false,this__9397.cnt);
} else
{return null;
}
});
cljs.core.PersistentTreeMap.prototype.toString = (function (){
var this__9398 = this;
var this__9399 = this;
return cljs.core.pr_str.call(null,this__9399);
});
cljs.core.PersistentTreeMap.prototype.entry_at = (function (k){
var this__9400 = this;
var coll__9401 = this;
var t__9402 = this__9400.tree;
while(true){
if(!((t__9402 == null)))
{var c__9403 = this__9400.comp.call(null,k,t__9402.key);
if((c__9403 === 0))
{return t__9402;
} else
{if((c__9403 < 0))
{{
var G__9421 = t__9402.left;
t__9402 = G__9421;
continue;
}
} else
{if("\uFDD0'else")
{{
var G__9422 = t__9402.right;
t__9402 = G__9422;
continue;
}
} else
{return null;
}
}
}
} else
{return null;
}
break;
}
});
cljs.core.PersistentTreeMap.prototype.cljs$core$ISorted$_sorted_seq$arity$2 = (function (coll,ascending_QMARK_){
var this__9404 = this;
if((this__9404.cnt > 0))
{return cljs.core.create_tree_map_seq.call(null,this__9404.tree,ascending_QMARK_,this__9404.cnt);
} else
{return null;
}
});
cljs.core.PersistentTreeMap.prototype.cljs$core$ISorted$_sorted_seq_from$arity$3 = (function (coll,k,ascending_QMARK_){
var this__9405 = this;
if((this__9405.cnt > 0))
{var stack__9406 = null;
var t__9407 = this__9405.tree;
while(true){
if(!((t__9407 == null)))
{var c__9408 = this__9405.comp.call(null,k,t__9407.key);
if((c__9408 === 0))
{return (new cljs.core.PersistentTreeMapSeq(null,cljs.core.conj.call(null,stack__9406,t__9407),ascending_QMARK_,-1,null));
} else
{if(cljs.core.truth_(ascending_QMARK_))
{if((c__9408 < 0))
{{
var G__9423 = cljs.core.conj.call(null,stack__9406,t__9407);
var G__9424 = t__9407.left;
stack__9406 = G__9423;
t__9407 = G__9424;
continue;
}
} else
{{
var G__9425 = stack__9406;
var G__9426 = t__9407.right;
stack__9406 = G__9425;
t__9407 = G__9426;
continue;
}
}
} else
{if("\uFDD0'else")
{if((c__9408 > 0))
{{
var G__9427 = cljs.core.conj.call(null,stack__9406,t__9407);
var G__9428 = t__9407.right;
stack__9406 = G__9427;
t__9407 = G__9428;
continue;
}
} else
{{
var G__9429 = stack__9406;
var G__9430 = t__9407.left;
stack__9406 = G__9429;
t__9407 = G__9430;
continue;
}
}
} else
{return null;
}
}
}
} else
{if((stack__9406 == null))
{return (new cljs.core.PersistentTreeMapSeq(null,stack__9406,ascending_QMARK_,-1,null));
} else
{return null;
}
}
break;
}
} else
{return null;
}
});
cljs.core.PersistentTreeMap.prototype.cljs$core$ISorted$_entry_key$arity$2 = (function (coll,entry){
var this__9409 = this;
return cljs.core.key.call(null,entry);
});
cljs.core.PersistentTreeMap.prototype.cljs$core$ISorted$_comparator$arity$1 = (function (coll){
var this__9410 = this;
return this__9410.comp;
});
cljs.core.PersistentTreeMap.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (coll){
var this__9411 = this;
if((this__9411.cnt > 0))
{return cljs.core.create_tree_map_seq.call(null,this__9411.tree,true,this__9411.cnt);
} else
{return null;
}
});
cljs.core.PersistentTreeMap.prototype.cljs$core$ICounted$_count$arity$1 = (function (coll){
var this__9412 = this;
return this__9412.cnt;
});
cljs.core.PersistentTreeMap.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (coll,other){
var this__9413 = this;
return cljs.core.equiv_map.call(null,coll,other);
});
cljs.core.PersistentTreeMap.prototype.cljs$core$IWithMeta$_with_meta$arity$2 = (function (coll,meta){
var this__9414 = this;
return (new cljs.core.PersistentTreeMap(this__9414.comp,this__9414.tree,this__9414.cnt,meta,this__9414.__hash));
});
cljs.core.PersistentTreeMap.prototype.cljs$core$IMeta$_meta$arity$1 = (function (coll){
var this__9415 = this;
return this__9415.meta;
});
cljs.core.PersistentTreeMap.prototype.cljs$core$IEmptyableCollection$_empty$arity$1 = (function (coll){
var this__9416 = this;
return cljs.core.with_meta.call(null,cljs.core.PersistentTreeMap.EMPTY,this__9416.meta);
});
cljs.core.PersistentTreeMap.prototype.cljs$core$IMap$_dissoc$arity$2 = (function (coll,k){
var this__9417 = this;
var found__9418 = [null];
var t__9419 = cljs.core.tree_map_remove.call(null,this__9417.comp,this__9417.tree,k,found__9418);
if((t__9419 == null))
{if((cljs.core.nth.call(null,found__9418,0) == null))
{return coll;
} else
{return (new cljs.core.PersistentTreeMap(this__9417.comp,null,0,this__9417.meta,null));
}
} else
{return (new cljs.core.PersistentTreeMap(this__9417.comp,t__9419.blacken(),(this__9417.cnt - 1),this__9417.meta,null));
}
});
cljs.core.PersistentTreeMap;
cljs.core.PersistentTreeMap.EMPTY = (new cljs.core.PersistentTreeMap(cljs.core.compare,null,0,null,0));
/**
* keyval => key val
* Returns a new hash map with supplied mappings.
* @param {...*} var_args
*/
cljs.core.hash_map = (function() { 
var hash_map__delegate = function (keyvals){
var in__9433 = cljs.core.seq.call(null,keyvals);
var out__9434 = cljs.core.transient$.call(null,cljs.core.PersistentHashMap.EMPTY);
while(true){
if(in__9433)
{{
var G__9435 = cljs.core.nnext.call(null,in__9433);
var G__9436 = cljs.core.assoc_BANG_.call(null,out__9434,cljs.core.first.call(null,in__9433),cljs.core.second.call(null,in__9433));
in__9433 = G__9435;
out__9434 = G__9436;
continue;
}
} else
{return cljs.core.persistent_BANG_.call(null,out__9434);
}
break;
}
};
var hash_map = function (var_args){
var keyvals = null;
if (goog.isDef(var_args)) {
  keyvals = cljs.core.array_seq(Array.prototype.slice.call(arguments, 0),0);
} 
return hash_map__delegate.call(this, keyvals);
};
hash_map.cljs$lang$maxFixedArity = 0;
hash_map.cljs$lang$applyTo = (function (arglist__9437){
var keyvals = cljs.core.seq(arglist__9437);;
return hash_map__delegate(keyvals);
});
hash_map.cljs$lang$arity$variadic = hash_map__delegate;
return hash_map;
})()
;
/**
* keyval => key val
* Returns a new array map with supplied mappings.
* @param {...*} var_args
*/
cljs.core.array_map = (function() { 
var array_map__delegate = function (keyvals){
return (new cljs.core.PersistentArrayMap(null,cljs.core.quot.call(null,cljs.core.count.call(null,keyvals),2),cljs.core.apply.call(null,cljs.core.array,keyvals),null));
};
var array_map = function (var_args){
var keyvals = null;
if (goog.isDef(var_args)) {
  keyvals = cljs.core.array_seq(Array.prototype.slice.call(arguments, 0),0);
} 
return array_map__delegate.call(this, keyvals);
};
array_map.cljs$lang$maxFixedArity = 0;
array_map.cljs$lang$applyTo = (function (arglist__9438){
var keyvals = cljs.core.seq(arglist__9438);;
return array_map__delegate(keyvals);
});
array_map.cljs$lang$arity$variadic = array_map__delegate;
return array_map;
})()
;
/**
* keyval => key val
* Returns a new object map with supplied mappings.
* @param {...*} var_args
*/
cljs.core.obj_map = (function() { 
var obj_map__delegate = function (keyvals){
var ks__9442 = [];
var obj__9443 = {};
var kvs__9444 = cljs.core.seq.call(null,keyvals);
while(true){
if(kvs__9444)
{ks__9442.push(cljs.core.first.call(null,kvs__9444));
(obj__9443[cljs.core.first.call(null,kvs__9444)] = cljs.core.second.call(null,kvs__9444));
{
var G__9445 = cljs.core.nnext.call(null,kvs__9444);
kvs__9444 = G__9445;
continue;
}
} else
{return cljs.core.ObjMap.fromObject.call(null,ks__9442,obj__9443);
}
break;
}
};
var obj_map = function (var_args){
var keyvals = null;
if (goog.isDef(var_args)) {
  keyvals = cljs.core.array_seq(Array.prototype.slice.call(arguments, 0),0);
} 
return obj_map__delegate.call(this, keyvals);
};
obj_map.cljs$lang$maxFixedArity = 0;
obj_map.cljs$lang$applyTo = (function (arglist__9446){
var keyvals = cljs.core.seq(arglist__9446);;
return obj_map__delegate(keyvals);
});
obj_map.cljs$lang$arity$variadic = obj_map__delegate;
return obj_map;
})()
;
/**
* keyval => key val
* Returns a new sorted map with supplied mappings.
* @param {...*} var_args
*/
cljs.core.sorted_map = (function() { 
var sorted_map__delegate = function (keyvals){
var in__9449 = cljs.core.seq.call(null,keyvals);
var out__9450 = cljs.core.PersistentTreeMap.EMPTY;
while(true){
if(in__9449)
{{
var G__9451 = cljs.core.nnext.call(null,in__9449);
var G__9452 = cljs.core.assoc.call(null,out__9450,cljs.core.first.call(null,in__9449),cljs.core.second.call(null,in__9449));
in__9449 = G__9451;
out__9450 = G__9452;
continue;
}
} else
{return out__9450;
}
break;
}
};
var sorted_map = function (var_args){
var keyvals = null;
if (goog.isDef(var_args)) {
  keyvals = cljs.core.array_seq(Array.prototype.slice.call(arguments, 0),0);
} 
return sorted_map__delegate.call(this, keyvals);
};
sorted_map.cljs$lang$maxFixedArity = 0;
sorted_map.cljs$lang$applyTo = (function (arglist__9453){
var keyvals = cljs.core.seq(arglist__9453);;
return sorted_map__delegate(keyvals);
});
sorted_map.cljs$lang$arity$variadic = sorted_map__delegate;
return sorted_map;
})()
;
/**
* keyval => key val
* Returns a new sorted map with supplied mappings, using the supplied comparator.
* @param {...*} var_args
*/
cljs.core.sorted_map_by = (function() { 
var sorted_map_by__delegate = function (comparator,keyvals){
var in__9456 = cljs.core.seq.call(null,keyvals);
var out__9457 = (new cljs.core.PersistentTreeMap(comparator,null,0,null,0));
while(true){
if(in__9456)
{{
var G__9458 = cljs.core.nnext.call(null,in__9456);
var G__9459 = cljs.core.assoc.call(null,out__9457,cljs.core.first.call(null,in__9456),cljs.core.second.call(null,in__9456));
in__9456 = G__9458;
out__9457 = G__9459;
continue;
}
} else
{return out__9457;
}
break;
}
};
var sorted_map_by = function (comparator,var_args){
var keyvals = null;
if (goog.isDef(var_args)) {
  keyvals = cljs.core.array_seq(Array.prototype.slice.call(arguments, 1),0);
} 
return sorted_map_by__delegate.call(this, comparator, keyvals);
};
sorted_map_by.cljs$lang$maxFixedArity = 1;
sorted_map_by.cljs$lang$applyTo = (function (arglist__9460){
var comparator = cljs.core.first(arglist__9460);
var keyvals = cljs.core.rest(arglist__9460);
return sorted_map_by__delegate(comparator, keyvals);
});
sorted_map_by.cljs$lang$arity$variadic = sorted_map_by__delegate;
return sorted_map_by;
})()
;
/**
* Returns a sequence of the map's keys.
*/
cljs.core.keys = (function keys(hash_map){
return cljs.core.seq.call(null,cljs.core.map.call(null,cljs.core.first,hash_map));
});
/**
* Returns the key of the map entry.
*/
cljs.core.key = (function key(map_entry){
return cljs.core._key.call(null,map_entry);
});
/**
* Returns a sequence of the map's values.
*/
cljs.core.vals = (function vals(hash_map){
return cljs.core.seq.call(null,cljs.core.map.call(null,cljs.core.second,hash_map));
});
/**
* Returns the value in the map entry.
*/
cljs.core.val = (function val(map_entry){
return cljs.core._val.call(null,map_entry);
});
/**
* Returns a map that consists of the rest of the maps conj-ed onto
* the first.  If a key occurs in more than one map, the mapping from
* the latter (left-to-right) will be the mapping in the result.
* @param {...*} var_args
*/
cljs.core.merge = (function() { 
var merge__delegate = function (maps){
if(cljs.core.truth_(cljs.core.some.call(null,cljs.core.identity,maps)))
{return cljs.core.reduce.call(null,(function (p1__9461_SHARP_,p2__9462_SHARP_){
return cljs.core.conj.call(null,(function (){var or__3824__auto____9464 = p1__9461_SHARP_;
if(cljs.core.truth_(or__3824__auto____9464))
{return or__3824__auto____9464;
} else
{return cljs.core.ObjMap.EMPTY;
}
})(),p2__9462_SHARP_);
}),maps);
} else
{return null;
}
};
var merge = function (var_args){
var maps = null;
if (goog.isDef(var_args)) {
  maps = cljs.core.array_seq(Array.prototype.slice.call(arguments, 0),0);
} 
return merge__delegate.call(this, maps);
};
merge.cljs$lang$maxFixedArity = 0;
merge.cljs$lang$applyTo = (function (arglist__9465){
var maps = cljs.core.seq(arglist__9465);;
return merge__delegate(maps);
});
merge.cljs$lang$arity$variadic = merge__delegate;
return merge;
})()
;
/**
* Returns a map that consists of the rest of the maps conj-ed onto
* the first.  If a key occurs in more than one map, the mapping(s)
* from the latter (left-to-right) will be combined with the mapping in
* the result by calling (f val-in-result val-in-latter).
* @param {...*} var_args
*/
cljs.core.merge_with = (function() { 
var merge_with__delegate = function (f,maps){
if(cljs.core.truth_(cljs.core.some.call(null,cljs.core.identity,maps)))
{var merge_entry__9473 = (function (m,e){
var k__9471 = cljs.core.first.call(null,e);
var v__9472 = cljs.core.second.call(null,e);
if(cljs.core.contains_QMARK_.call(null,m,k__9471))
{return cljs.core.assoc.call(null,m,k__9471,f.call(null,cljs.core._lookup.call(null,m,k__9471,null),v__9472));
} else
{return cljs.core.assoc.call(null,m,k__9471,v__9472);
}
});
var merge2__9475 = (function (m1,m2){
return cljs.core.reduce.call(null,merge_entry__9473,(function (){var or__3824__auto____9474 = m1;
if(cljs.core.truth_(or__3824__auto____9474))
{return or__3824__auto____9474;
} else
{return cljs.core.ObjMap.EMPTY;
}
})(),cljs.core.seq.call(null,m2));
});
return cljs.core.reduce.call(null,merge2__9475,maps);
} else
{return null;
}
};
var merge_with = function (f,var_args){
var maps = null;
if (goog.isDef(var_args)) {
  maps = cljs.core.array_seq(Array.prototype.slice.call(arguments, 1),0);
} 
return merge_with__delegate.call(this, f, maps);
};
merge_with.cljs$lang$maxFixedArity = 1;
merge_with.cljs$lang$applyTo = (function (arglist__9476){
var f = cljs.core.first(arglist__9476);
var maps = cljs.core.rest(arglist__9476);
return merge_with__delegate(f, maps);
});
merge_with.cljs$lang$arity$variadic = merge_with__delegate;
return merge_with;
})()
;
/**
* Returns a map containing only those entries in map whose key is in keys
*/
cljs.core.select_keys = (function select_keys(map,keyseq){
var ret__9481 = cljs.core.ObjMap.EMPTY;
var keys__9482 = cljs.core.seq.call(null,keyseq);
while(true){
if(keys__9482)
{var key__9483 = cljs.core.first.call(null,keys__9482);
var entry__9484 = cljs.core._lookup.call(null,map,key__9483,"\uFDD0'cljs.core/not-found");
{
var G__9485 = ((cljs.core.not_EQ_.call(null,entry__9484,"\uFDD0'cljs.core/not-found"))?cljs.core.assoc.call(null,ret__9481,key__9483,entry__9484):ret__9481);
var G__9486 = cljs.core.next.call(null,keys__9482);
ret__9481 = G__9485;
keys__9482 = G__9486;
continue;
}
} else
{return ret__9481;
}
break;
}
});

/**
* @constructor
*/
cljs.core.PersistentHashSet = (function (meta,hash_map,__hash){
this.meta = meta;
this.hash_map = hash_map;
this.__hash = __hash;
this.cljs$lang$protocol_mask$partition1$ = 1;
this.cljs$lang$protocol_mask$partition0$ = 15077647;
})
cljs.core.PersistentHashSet.cljs$lang$type = true;
cljs.core.PersistentHashSet.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/PersistentHashSet");
});
cljs.core.PersistentHashSet.prototype.cljs$core$IEditableCollection$_as_transient$arity$1 = (function (coll){
var this__9490 = this;
return (new cljs.core.TransientHashSet(cljs.core.transient$.call(null,this__9490.hash_map)));
});
cljs.core.PersistentHashSet.prototype.cljs$core$IHash$_hash$arity$1 = (function (coll){
var this__9491 = this;
var h__2220__auto____9492 = this__9491.__hash;
if(!((h__2220__auto____9492 == null)))
{return h__2220__auto____9492;
} else
{var h__2220__auto____9493 = cljs.core.hash_iset.call(null,coll);
this__9491.__hash = h__2220__auto____9493;
return h__2220__auto____9493;
}
});
cljs.core.PersistentHashSet.prototype.cljs$core$ILookup$_lookup$arity$2 = (function (coll,v){
var this__9494 = this;
return coll.cljs$core$ILookup$_lookup$arity$3(coll,v,null);
});
cljs.core.PersistentHashSet.prototype.cljs$core$ILookup$_lookup$arity$3 = (function (coll,v,not_found){
var this__9495 = this;
if(cljs.core.truth_(cljs.core._contains_key_QMARK_.call(null,this__9495.hash_map,v)))
{return v;
} else
{return not_found;
}
});
cljs.core.PersistentHashSet.prototype.call = (function() {
var G__9516 = null;
var G__9516__2 = (function (this_sym9496,k){
var this__9498 = this;
var this_sym9496__9499 = this;
var coll__9500 = this_sym9496__9499;
return coll__9500.cljs$core$ILookup$_lookup$arity$2(coll__9500,k);
});
var G__9516__3 = (function (this_sym9497,k,not_found){
var this__9498 = this;
var this_sym9497__9501 = this;
var coll__9502 = this_sym9497__9501;
return coll__9502.cljs$core$ILookup$_lookup$arity$3(coll__9502,k,not_found);
});
G__9516 = function(this_sym9497,k,not_found){
switch(arguments.length){
case 2:
return G__9516__2.call(this,this_sym9497,k);
case 3:
return G__9516__3.call(this,this_sym9497,k,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
return G__9516;
})()
;
cljs.core.PersistentHashSet.prototype.apply = (function (this_sym9488,args9489){
var this__9503 = this;
return this_sym9488.call.apply(this_sym9488,[this_sym9488].concat(args9489.slice()));
});
cljs.core.PersistentHashSet.prototype.cljs$core$ICollection$_conj$arity$2 = (function (coll,o){
var this__9504 = this;
return (new cljs.core.PersistentHashSet(this__9504.meta,cljs.core.assoc.call(null,this__9504.hash_map,o,null),null));
});
cljs.core.PersistentHashSet.prototype.toString = (function (){
var this__9505 = this;
var this__9506 = this;
return cljs.core.pr_str.call(null,this__9506);
});
cljs.core.PersistentHashSet.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (coll){
var this__9507 = this;
return cljs.core.keys.call(null,this__9507.hash_map);
});
cljs.core.PersistentHashSet.prototype.cljs$core$ISet$_disjoin$arity$2 = (function (coll,v){
var this__9508 = this;
return (new cljs.core.PersistentHashSet(this__9508.meta,cljs.core.dissoc.call(null,this__9508.hash_map,v),null));
});
cljs.core.PersistentHashSet.prototype.cljs$core$ICounted$_count$arity$1 = (function (coll){
var this__9509 = this;
return cljs.core.count.call(null,cljs.core.seq.call(null,coll));
});
cljs.core.PersistentHashSet.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (coll,other){
var this__9510 = this;
var and__3822__auto____9511 = cljs.core.set_QMARK_.call(null,other);
if(and__3822__auto____9511)
{var and__3822__auto____9512 = (cljs.core.count.call(null,coll) === cljs.core.count.call(null,other));
if(and__3822__auto____9512)
{return cljs.core.every_QMARK_.call(null,(function (p1__9487_SHARP_){
return cljs.core.contains_QMARK_.call(null,coll,p1__9487_SHARP_);
}),other);
} else
{return and__3822__auto____9512;
}
} else
{return and__3822__auto____9511;
}
});
cljs.core.PersistentHashSet.prototype.cljs$core$IWithMeta$_with_meta$arity$2 = (function (coll,meta){
var this__9513 = this;
return (new cljs.core.PersistentHashSet(meta,this__9513.hash_map,this__9513.__hash));
});
cljs.core.PersistentHashSet.prototype.cljs$core$IMeta$_meta$arity$1 = (function (coll){
var this__9514 = this;
return this__9514.meta;
});
cljs.core.PersistentHashSet.prototype.cljs$core$IEmptyableCollection$_empty$arity$1 = (function (coll){
var this__9515 = this;
return cljs.core.with_meta.call(null,cljs.core.PersistentHashSet.EMPTY,this__9515.meta);
});
cljs.core.PersistentHashSet;
cljs.core.PersistentHashSet.EMPTY = (new cljs.core.PersistentHashSet(null,cljs.core.hash_map.call(null),0));
cljs.core.PersistentHashSet.fromArray = (function (items){
var len__9517 = cljs.core.count.call(null,items);
var i__9518 = 0;
var out__9519 = cljs.core.transient$.call(null,cljs.core.PersistentHashSet.EMPTY);
while(true){
if((i__9518 < len__9517))
{{
var G__9520 = (i__9518 + 1);
var G__9521 = cljs.core.conj_BANG_.call(null,out__9519,(items[i__9518]));
i__9518 = G__9520;
out__9519 = G__9521;
continue;
}
} else
{return cljs.core.persistent_BANG_.call(null,out__9519);
}
break;
}
});

/**
* @constructor
*/
cljs.core.TransientHashSet = (function (transient_map){
this.transient_map = transient_map;
this.cljs$lang$protocol_mask$partition0$ = 259;
this.cljs$lang$protocol_mask$partition1$ = 34;
})
cljs.core.TransientHashSet.cljs$lang$type = true;
cljs.core.TransientHashSet.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/TransientHashSet");
});
cljs.core.TransientHashSet.prototype.call = (function() {
var G__9539 = null;
var G__9539__2 = (function (this_sym9525,k){
var this__9527 = this;
var this_sym9525__9528 = this;
var tcoll__9529 = this_sym9525__9528;
if((cljs.core._lookup.call(null,this__9527.transient_map,k,cljs.core.lookup_sentinel) === cljs.core.lookup_sentinel))
{return null;
} else
{return k;
}
});
var G__9539__3 = (function (this_sym9526,k,not_found){
var this__9527 = this;
var this_sym9526__9530 = this;
var tcoll__9531 = this_sym9526__9530;
if((cljs.core._lookup.call(null,this__9527.transient_map,k,cljs.core.lookup_sentinel) === cljs.core.lookup_sentinel))
{return not_found;
} else
{return k;
}
});
G__9539 = function(this_sym9526,k,not_found){
switch(arguments.length){
case 2:
return G__9539__2.call(this,this_sym9526,k);
case 3:
return G__9539__3.call(this,this_sym9526,k,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
return G__9539;
})()
;
cljs.core.TransientHashSet.prototype.apply = (function (this_sym9523,args9524){
var this__9532 = this;
return this_sym9523.call.apply(this_sym9523,[this_sym9523].concat(args9524.slice()));
});
cljs.core.TransientHashSet.prototype.cljs$core$ILookup$_lookup$arity$2 = (function (tcoll,v){
var this__9533 = this;
return tcoll.cljs$core$ILookup$_lookup$arity$3(tcoll,v,null);
});
cljs.core.TransientHashSet.prototype.cljs$core$ILookup$_lookup$arity$3 = (function (tcoll,v,not_found){
var this__9534 = this;
if((cljs.core._lookup.call(null,this__9534.transient_map,v,cljs.core.lookup_sentinel) === cljs.core.lookup_sentinel))
{return not_found;
} else
{return v;
}
});
cljs.core.TransientHashSet.prototype.cljs$core$ICounted$_count$arity$1 = (function (tcoll){
var this__9535 = this;
return cljs.core.count.call(null,this__9535.transient_map);
});
cljs.core.TransientHashSet.prototype.cljs$core$ITransientSet$_disjoin_BANG_$arity$2 = (function (tcoll,v){
var this__9536 = this;
this__9536.transient_map = cljs.core.dissoc_BANG_.call(null,this__9536.transient_map,v);
return tcoll;
});
cljs.core.TransientHashSet.prototype.cljs$core$ITransientCollection$_conj_BANG_$arity$2 = (function (tcoll,o){
var this__9537 = this;
this__9537.transient_map = cljs.core.assoc_BANG_.call(null,this__9537.transient_map,o,null);
return tcoll;
});
cljs.core.TransientHashSet.prototype.cljs$core$ITransientCollection$_persistent_BANG_$arity$1 = (function (tcoll){
var this__9538 = this;
return (new cljs.core.PersistentHashSet(null,cljs.core.persistent_BANG_.call(null,this__9538.transient_map),null));
});
cljs.core.TransientHashSet;

/**
* @constructor
*/
cljs.core.PersistentTreeSet = (function (meta,tree_map,__hash){
this.meta = meta;
this.tree_map = tree_map;
this.__hash = __hash;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 417730831;
})
cljs.core.PersistentTreeSet.cljs$lang$type = true;
cljs.core.PersistentTreeSet.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/PersistentTreeSet");
});
cljs.core.PersistentTreeSet.prototype.cljs$core$IHash$_hash$arity$1 = (function (coll){
var this__9542 = this;
var h__2220__auto____9543 = this__9542.__hash;
if(!((h__2220__auto____9543 == null)))
{return h__2220__auto____9543;
} else
{var h__2220__auto____9544 = cljs.core.hash_iset.call(null,coll);
this__9542.__hash = h__2220__auto____9544;
return h__2220__auto____9544;
}
});
cljs.core.PersistentTreeSet.prototype.cljs$core$ILookup$_lookup$arity$2 = (function (coll,v){
var this__9545 = this;
return coll.cljs$core$ILookup$_lookup$arity$3(coll,v,null);
});
cljs.core.PersistentTreeSet.prototype.cljs$core$ILookup$_lookup$arity$3 = (function (coll,v,not_found){
var this__9546 = this;
if(cljs.core.truth_(cljs.core._contains_key_QMARK_.call(null,this__9546.tree_map,v)))
{return v;
} else
{return not_found;
}
});
cljs.core.PersistentTreeSet.prototype.call = (function() {
var G__9572 = null;
var G__9572__2 = (function (this_sym9547,k){
var this__9549 = this;
var this_sym9547__9550 = this;
var coll__9551 = this_sym9547__9550;
return coll__9551.cljs$core$ILookup$_lookup$arity$2(coll__9551,k);
});
var G__9572__3 = (function (this_sym9548,k,not_found){
var this__9549 = this;
var this_sym9548__9552 = this;
var coll__9553 = this_sym9548__9552;
return coll__9553.cljs$core$ILookup$_lookup$arity$3(coll__9553,k,not_found);
});
G__9572 = function(this_sym9548,k,not_found){
switch(arguments.length){
case 2:
return G__9572__2.call(this,this_sym9548,k);
case 3:
return G__9572__3.call(this,this_sym9548,k,not_found);
}
throw('Invalid arity: ' + arguments.length);
};
return G__9572;
})()
;
cljs.core.PersistentTreeSet.prototype.apply = (function (this_sym9540,args9541){
var this__9554 = this;
return this_sym9540.call.apply(this_sym9540,[this_sym9540].concat(args9541.slice()));
});
cljs.core.PersistentTreeSet.prototype.cljs$core$ICollection$_conj$arity$2 = (function (coll,o){
var this__9555 = this;
return (new cljs.core.PersistentTreeSet(this__9555.meta,cljs.core.assoc.call(null,this__9555.tree_map,o,null),null));
});
cljs.core.PersistentTreeSet.prototype.cljs$core$IReversible$_rseq$arity$1 = (function (coll){
var this__9556 = this;
return cljs.core.map.call(null,cljs.core.key,cljs.core.rseq.call(null,this__9556.tree_map));
});
cljs.core.PersistentTreeSet.prototype.toString = (function (){
var this__9557 = this;
var this__9558 = this;
return cljs.core.pr_str.call(null,this__9558);
});
cljs.core.PersistentTreeSet.prototype.cljs$core$ISorted$_sorted_seq$arity$2 = (function (coll,ascending_QMARK_){
var this__9559 = this;
return cljs.core.map.call(null,cljs.core.key,cljs.core._sorted_seq.call(null,this__9559.tree_map,ascending_QMARK_));
});
cljs.core.PersistentTreeSet.prototype.cljs$core$ISorted$_sorted_seq_from$arity$3 = (function (coll,k,ascending_QMARK_){
var this__9560 = this;
return cljs.core.map.call(null,cljs.core.key,cljs.core._sorted_seq_from.call(null,this__9560.tree_map,k,ascending_QMARK_));
});
cljs.core.PersistentTreeSet.prototype.cljs$core$ISorted$_entry_key$arity$2 = (function (coll,entry){
var this__9561 = this;
return entry;
});
cljs.core.PersistentTreeSet.prototype.cljs$core$ISorted$_comparator$arity$1 = (function (coll){
var this__9562 = this;
return cljs.core._comparator.call(null,this__9562.tree_map);
});
cljs.core.PersistentTreeSet.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (coll){
var this__9563 = this;
return cljs.core.keys.call(null,this__9563.tree_map);
});
cljs.core.PersistentTreeSet.prototype.cljs$core$ISet$_disjoin$arity$2 = (function (coll,v){
var this__9564 = this;
return (new cljs.core.PersistentTreeSet(this__9564.meta,cljs.core.dissoc.call(null,this__9564.tree_map,v),null));
});
cljs.core.PersistentTreeSet.prototype.cljs$core$ICounted$_count$arity$1 = (function (coll){
var this__9565 = this;
return cljs.core.count.call(null,this__9565.tree_map);
});
cljs.core.PersistentTreeSet.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (coll,other){
var this__9566 = this;
var and__3822__auto____9567 = cljs.core.set_QMARK_.call(null,other);
if(and__3822__auto____9567)
{var and__3822__auto____9568 = (cljs.core.count.call(null,coll) === cljs.core.count.call(null,other));
if(and__3822__auto____9568)
{return cljs.core.every_QMARK_.call(null,(function (p1__9522_SHARP_){
return cljs.core.contains_QMARK_.call(null,coll,p1__9522_SHARP_);
}),other);
} else
{return and__3822__auto____9568;
}
} else
{return and__3822__auto____9567;
}
});
cljs.core.PersistentTreeSet.prototype.cljs$core$IWithMeta$_with_meta$arity$2 = (function (coll,meta){
var this__9569 = this;
return (new cljs.core.PersistentTreeSet(meta,this__9569.tree_map,this__9569.__hash));
});
cljs.core.PersistentTreeSet.prototype.cljs$core$IMeta$_meta$arity$1 = (function (coll){
var this__9570 = this;
return this__9570.meta;
});
cljs.core.PersistentTreeSet.prototype.cljs$core$IEmptyableCollection$_empty$arity$1 = (function (coll){
var this__9571 = this;
return cljs.core.with_meta.call(null,cljs.core.PersistentTreeSet.EMPTY,this__9571.meta);
});
cljs.core.PersistentTreeSet;
cljs.core.PersistentTreeSet.EMPTY = (new cljs.core.PersistentTreeSet(null,cljs.core.sorted_map.call(null),0));
/**
* @param {...*} var_args
*/
cljs.core.hash_set = (function() {
var hash_set = null;
var hash_set__0 = (function (){
return cljs.core.PersistentHashSet.EMPTY;
});
var hash_set__1 = (function() { 
var G__9577__delegate = function (keys){
var in__9575 = cljs.core.seq.call(null,keys);
var out__9576 = cljs.core.transient$.call(null,cljs.core.PersistentHashSet.EMPTY);
while(true){
if(cljs.core.seq.call(null,in__9575))
{{
var G__9578 = cljs.core.next.call(null,in__9575);
var G__9579 = cljs.core.conj_BANG_.call(null,out__9576,cljs.core.first.call(null,in__9575));
in__9575 = G__9578;
out__9576 = G__9579;
continue;
}
} else
{return cljs.core.persistent_BANG_.call(null,out__9576);
}
break;
}
};
var G__9577 = function (var_args){
var keys = null;
if (goog.isDef(var_args)) {
  keys = cljs.core.array_seq(Array.prototype.slice.call(arguments, 0),0);
} 
return G__9577__delegate.call(this, keys);
};
G__9577.cljs$lang$maxFixedArity = 0;
G__9577.cljs$lang$applyTo = (function (arglist__9580){
var keys = cljs.core.seq(arglist__9580);;
return G__9577__delegate(keys);
});
G__9577.cljs$lang$arity$variadic = G__9577__delegate;
return G__9577;
})()
;
hash_set = function(var_args){
var keys = var_args;
switch(arguments.length){
case 0:
return hash_set__0.call(this);
default:
return hash_set__1.cljs$lang$arity$variadic(cljs.core.array_seq(arguments, 0));
}
throw('Invalid arity: ' + arguments.length);
};
hash_set.cljs$lang$maxFixedArity = 0;
hash_set.cljs$lang$applyTo = hash_set__1.cljs$lang$applyTo;
hash_set.cljs$lang$arity$0 = hash_set__0;
hash_set.cljs$lang$arity$variadic = hash_set__1.cljs$lang$arity$variadic;
return hash_set;
})()
;
/**
* Returns a set of the distinct elements of coll.
*/
cljs.core.set = (function set(coll){
return cljs.core.apply.call(null,cljs.core.hash_set,coll);
});
/**
* Returns a new sorted set with supplied keys.
* @param {...*} var_args
*/
cljs.core.sorted_set = (function() { 
var sorted_set__delegate = function (keys){
return cljs.core.reduce.call(null,cljs.core._conj,cljs.core.PersistentTreeSet.EMPTY,keys);
};
var sorted_set = function (var_args){
var keys = null;
if (goog.isDef(var_args)) {
  keys = cljs.core.array_seq(Array.prototype.slice.call(arguments, 0),0);
} 
return sorted_set__delegate.call(this, keys);
};
sorted_set.cljs$lang$maxFixedArity = 0;
sorted_set.cljs$lang$applyTo = (function (arglist__9581){
var keys = cljs.core.seq(arglist__9581);;
return sorted_set__delegate(keys);
});
sorted_set.cljs$lang$arity$variadic = sorted_set__delegate;
return sorted_set;
})()
;
/**
* Returns a new sorted set with supplied keys, using the supplied comparator.
* @param {...*} var_args
*/
cljs.core.sorted_set_by = (function() { 
var sorted_set_by__delegate = function (comparator,keys){
return cljs.core.reduce.call(null,cljs.core._conj,(new cljs.core.PersistentTreeSet(null,cljs.core.sorted_map_by.call(null,comparator),0)),keys);
};
var sorted_set_by = function (comparator,var_args){
var keys = null;
if (goog.isDef(var_args)) {
  keys = cljs.core.array_seq(Array.prototype.slice.call(arguments, 1),0);
} 
return sorted_set_by__delegate.call(this, comparator, keys);
};
sorted_set_by.cljs$lang$maxFixedArity = 1;
sorted_set_by.cljs$lang$applyTo = (function (arglist__9583){
var comparator = cljs.core.first(arglist__9583);
var keys = cljs.core.rest(arglist__9583);
return sorted_set_by__delegate(comparator, keys);
});
sorted_set_by.cljs$lang$arity$variadic = sorted_set_by__delegate;
return sorted_set_by;
})()
;
/**
* Given a map of replacement pairs and a vector/collection, returns a
* vector/seq with any elements = a key in smap replaced with the
* corresponding val in smap
*/
cljs.core.replace = (function replace(smap,coll){
if(cljs.core.vector_QMARK_.call(null,coll))
{var n__9589 = cljs.core.count.call(null,coll);
return cljs.core.reduce.call(null,(function (v,i){
var temp__3971__auto____9590 = cljs.core.find.call(null,smap,cljs.core.nth.call(null,v,i));
if(cljs.core.truth_(temp__3971__auto____9590))
{var e__9591 = temp__3971__auto____9590;
return cljs.core.assoc.call(null,v,i,cljs.core.second.call(null,e__9591));
} else
{return v;
}
}),coll,cljs.core.take.call(null,n__9589,cljs.core.iterate.call(null,cljs.core.inc,0)));
} else
{return cljs.core.map.call(null,(function (p1__9582_SHARP_){
var temp__3971__auto____9592 = cljs.core.find.call(null,smap,p1__9582_SHARP_);
if(cljs.core.truth_(temp__3971__auto____9592))
{var e__9593 = temp__3971__auto____9592;
return cljs.core.second.call(null,e__9593);
} else
{return p1__9582_SHARP_;
}
}),coll);
}
});
/**
* Returns a lazy sequence of the elements of coll with duplicates removed
*/
cljs.core.distinct = (function distinct(coll){
var step__9623 = (function step(xs,seen){
return (new cljs.core.LazySeq(null,false,(function (){
return (function (p__9616,seen){
while(true){
var vec__9617__9618 = p__9616;
var f__9619 = cljs.core.nth.call(null,vec__9617__9618,0,null);
var xs__9620 = vec__9617__9618;
var temp__3974__auto____9621 = cljs.core.seq.call(null,xs__9620);
if(temp__3974__auto____9621)
{var s__9622 = temp__3974__auto____9621;
if(cljs.core.contains_QMARK_.call(null,seen,f__9619))
{{
var G__9624 = cljs.core.rest.call(null,s__9622);
var G__9625 = seen;
p__9616 = G__9624;
seen = G__9625;
continue;
}
} else
{return cljs.core.cons.call(null,f__9619,step.call(null,cljs.core.rest.call(null,s__9622),cljs.core.conj.call(null,seen,f__9619)));
}
} else
{return null;
}
break;
}
}).call(null,xs,seen);
}),null));
});
return step__9623.call(null,coll,cljs.core.PersistentHashSet.EMPTY);
});
cljs.core.butlast = (function butlast(s){
var ret__9628 = cljs.core.PersistentVector.EMPTY;
var s__9629 = s;
while(true){
if(cljs.core.next.call(null,s__9629))
{{
var G__9630 = cljs.core.conj.call(null,ret__9628,cljs.core.first.call(null,s__9629));
var G__9631 = cljs.core.next.call(null,s__9629);
ret__9628 = G__9630;
s__9629 = G__9631;
continue;
}
} else
{return cljs.core.seq.call(null,ret__9628);
}
break;
}
});
/**
* Returns the name String of a string, symbol or keyword.
*/
cljs.core.name = (function name(x){
if(cljs.core.string_QMARK_.call(null,x))
{return x;
} else
{if((function (){var or__3824__auto____9634 = cljs.core.keyword_QMARK_.call(null,x);
if(or__3824__auto____9634)
{return or__3824__auto____9634;
} else
{return cljs.core.symbol_QMARK_.call(null,x);
}
})())
{var i__9635 = x.lastIndexOf("/");
if((i__9635 < 0))
{return cljs.core.subs.call(null,x,2);
} else
{return cljs.core.subs.call(null,x,(i__9635 + 1));
}
} else
{if("\uFDD0'else")
{throw (new Error([cljs.core.str("Doesn't support name: "),cljs.core.str(x)].join('')));
} else
{return null;
}
}
}
});
/**
* Returns the namespace String of a symbol or keyword, or nil if not present.
*/
cljs.core.namespace = (function namespace(x){
if((function (){var or__3824__auto____9638 = cljs.core.keyword_QMARK_.call(null,x);
if(or__3824__auto____9638)
{return or__3824__auto____9638;
} else
{return cljs.core.symbol_QMARK_.call(null,x);
}
})())
{var i__9639 = x.lastIndexOf("/");
if((i__9639 > -1))
{return cljs.core.subs.call(null,x,2,i__9639);
} else
{return null;
}
} else
{throw (new Error([cljs.core.str("Doesn't support namespace: "),cljs.core.str(x)].join('')));
}
});
/**
* Returns a map with the keys mapped to the corresponding vals.
*/
cljs.core.zipmap = (function zipmap(keys,vals){
var map__9646 = cljs.core.ObjMap.EMPTY;
var ks__9647 = cljs.core.seq.call(null,keys);
var vs__9648 = cljs.core.seq.call(null,vals);
while(true){
if((function (){var and__3822__auto____9649 = ks__9647;
if(and__3822__auto____9649)
{return vs__9648;
} else
{return and__3822__auto____9649;
}
})())
{{
var G__9650 = cljs.core.assoc.call(null,map__9646,cljs.core.first.call(null,ks__9647),cljs.core.first.call(null,vs__9648));
var G__9651 = cljs.core.next.call(null,ks__9647);
var G__9652 = cljs.core.next.call(null,vs__9648);
map__9646 = G__9650;
ks__9647 = G__9651;
vs__9648 = G__9652;
continue;
}
} else
{return map__9646;
}
break;
}
});
/**
* Returns the x for which (k x), a number, is greatest.
* @param {...*} var_args
*/
cljs.core.max_key = (function() {
var max_key = null;
var max_key__2 = (function (k,x){
return x;
});
var max_key__3 = (function (k,x,y){
if((k.call(null,x) > k.call(null,y)))
{return x;
} else
{return y;
}
});
var max_key__4 = (function() { 
var G__9655__delegate = function (k,x,y,more){
return cljs.core.reduce.call(null,(function (p1__9640_SHARP_,p2__9641_SHARP_){
return max_key.call(null,k,p1__9640_SHARP_,p2__9641_SHARP_);
}),max_key.call(null,k,x,y),more);
};
var G__9655 = function (k,x,y,var_args){
var more = null;
if (goog.isDef(var_args)) {
  more = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return G__9655__delegate.call(this, k, x, y, more);
};
G__9655.cljs$lang$maxFixedArity = 3;
G__9655.cljs$lang$applyTo = (function (arglist__9656){
var k = cljs.core.first(arglist__9656);
var x = cljs.core.first(cljs.core.next(arglist__9656));
var y = cljs.core.first(cljs.core.next(cljs.core.next(arglist__9656)));
var more = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__9656)));
return G__9655__delegate(k, x, y, more);
});
G__9655.cljs$lang$arity$variadic = G__9655__delegate;
return G__9655;
})()
;
max_key = function(k,x,y,var_args){
var more = var_args;
switch(arguments.length){
case 2:
return max_key__2.call(this,k,x);
case 3:
return max_key__3.call(this,k,x,y);
default:
return max_key__4.cljs$lang$arity$variadic(k,x,y, cljs.core.array_seq(arguments, 3));
}
throw('Invalid arity: ' + arguments.length);
};
max_key.cljs$lang$maxFixedArity = 3;
max_key.cljs$lang$applyTo = max_key__4.cljs$lang$applyTo;
max_key.cljs$lang$arity$2 = max_key__2;
max_key.cljs$lang$arity$3 = max_key__3;
max_key.cljs$lang$arity$variadic = max_key__4.cljs$lang$arity$variadic;
return max_key;
})()
;
/**
* Returns the x for which (k x), a number, is least.
* @param {...*} var_args
*/
cljs.core.min_key = (function() {
var min_key = null;
var min_key__2 = (function (k,x){
return x;
});
var min_key__3 = (function (k,x,y){
if((k.call(null,x) < k.call(null,y)))
{return x;
} else
{return y;
}
});
var min_key__4 = (function() { 
var G__9657__delegate = function (k,x,y,more){
return cljs.core.reduce.call(null,(function (p1__9653_SHARP_,p2__9654_SHARP_){
return min_key.call(null,k,p1__9653_SHARP_,p2__9654_SHARP_);
}),min_key.call(null,k,x,y),more);
};
var G__9657 = function (k,x,y,var_args){
var more = null;
if (goog.isDef(var_args)) {
  more = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return G__9657__delegate.call(this, k, x, y, more);
};
G__9657.cljs$lang$maxFixedArity = 3;
G__9657.cljs$lang$applyTo = (function (arglist__9658){
var k = cljs.core.first(arglist__9658);
var x = cljs.core.first(cljs.core.next(arglist__9658));
var y = cljs.core.first(cljs.core.next(cljs.core.next(arglist__9658)));
var more = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__9658)));
return G__9657__delegate(k, x, y, more);
});
G__9657.cljs$lang$arity$variadic = G__9657__delegate;
return G__9657;
})()
;
min_key = function(k,x,y,var_args){
var more = var_args;
switch(arguments.length){
case 2:
return min_key__2.call(this,k,x);
case 3:
return min_key__3.call(this,k,x,y);
default:
return min_key__4.cljs$lang$arity$variadic(k,x,y, cljs.core.array_seq(arguments, 3));
}
throw('Invalid arity: ' + arguments.length);
};
min_key.cljs$lang$maxFixedArity = 3;
min_key.cljs$lang$applyTo = min_key__4.cljs$lang$applyTo;
min_key.cljs$lang$arity$2 = min_key__2;
min_key.cljs$lang$arity$3 = min_key__3;
min_key.cljs$lang$arity$variadic = min_key__4.cljs$lang$arity$variadic;
return min_key;
})()
;
/**
* Returns a lazy sequence of lists like partition, but may include
* partitions with fewer than n items at the end.
*/
cljs.core.partition_all = (function() {
var partition_all = null;
var partition_all__2 = (function (n,coll){
return partition_all.call(null,n,n,coll);
});
var partition_all__3 = (function (n,step,coll){
return (new cljs.core.LazySeq(null,false,(function (){
var temp__3974__auto____9661 = cljs.core.seq.call(null,coll);
if(temp__3974__auto____9661)
{var s__9662 = temp__3974__auto____9661;
return cljs.core.cons.call(null,cljs.core.take.call(null,n,s__9662),partition_all.call(null,n,step,cljs.core.drop.call(null,step,s__9662)));
} else
{return null;
}
}),null));
});
partition_all = function(n,step,coll){
switch(arguments.length){
case 2:
return partition_all__2.call(this,n,step);
case 3:
return partition_all__3.call(this,n,step,coll);
}
throw('Invalid arity: ' + arguments.length);
};
partition_all.cljs$lang$arity$2 = partition_all__2;
partition_all.cljs$lang$arity$3 = partition_all__3;
return partition_all;
})()
;
/**
* Returns a lazy sequence of successive items from coll while
* (pred item) returns true. pred must be free of side-effects.
*/
cljs.core.take_while = (function take_while(pred,coll){
return (new cljs.core.LazySeq(null,false,(function (){
var temp__3974__auto____9665 = cljs.core.seq.call(null,coll);
if(temp__3974__auto____9665)
{var s__9666 = temp__3974__auto____9665;
if(cljs.core.truth_(pred.call(null,cljs.core.first.call(null,s__9666))))
{return cljs.core.cons.call(null,cljs.core.first.call(null,s__9666),take_while.call(null,pred,cljs.core.rest.call(null,s__9666)));
} else
{return null;
}
} else
{return null;
}
}),null));
});
cljs.core.mk_bound_fn = (function mk_bound_fn(sc,test,key){
return (function (e){
var comp__9668 = cljs.core._comparator.call(null,sc);
return test.call(null,comp__9668.call(null,cljs.core._entry_key.call(null,sc,e),key),0);
});
});
/**
* sc must be a sorted collection, test(s) one of <, <=, > or
* >=. Returns a seq of those entries with keys ek for
* which (test (.. sc comparator (compare ek key)) 0) is true
*/
cljs.core.subseq = (function() {
var subseq = null;
var subseq__3 = (function (sc,test,key){
var include__9680 = cljs.core.mk_bound_fn.call(null,sc,test,key);
if(cljs.core.truth_(cljs.core.PersistentHashSet.fromArray([cljs.core._GT_,cljs.core._GT__EQ_]).call(null,test)))
{var temp__3974__auto____9681 = cljs.core._sorted_seq_from.call(null,sc,key,true);
if(cljs.core.truth_(temp__3974__auto____9681))
{var vec__9682__9683 = temp__3974__auto____9681;
var e__9684 = cljs.core.nth.call(null,vec__9682__9683,0,null);
var s__9685 = vec__9682__9683;
if(cljs.core.truth_(include__9680.call(null,e__9684)))
{return s__9685;
} else
{return cljs.core.next.call(null,s__9685);
}
} else
{return null;
}
} else
{return cljs.core.take_while.call(null,include__9680,cljs.core._sorted_seq.call(null,sc,true));
}
});
var subseq__5 = (function (sc,start_test,start_key,end_test,end_key){
var temp__3974__auto____9686 = cljs.core._sorted_seq_from.call(null,sc,start_key,true);
if(cljs.core.truth_(temp__3974__auto____9686))
{var vec__9687__9688 = temp__3974__auto____9686;
var e__9689 = cljs.core.nth.call(null,vec__9687__9688,0,null);
var s__9690 = vec__9687__9688;
return cljs.core.take_while.call(null,cljs.core.mk_bound_fn.call(null,sc,end_test,end_key),(cljs.core.truth_(cljs.core.mk_bound_fn.call(null,sc,start_test,start_key).call(null,e__9689))?s__9690:cljs.core.next.call(null,s__9690)));
} else
{return null;
}
});
subseq = function(sc,start_test,start_key,end_test,end_key){
switch(arguments.length){
case 3:
return subseq__3.call(this,sc,start_test,start_key);
case 5:
return subseq__5.call(this,sc,start_test,start_key,end_test,end_key);
}
throw('Invalid arity: ' + arguments.length);
};
subseq.cljs$lang$arity$3 = subseq__3;
subseq.cljs$lang$arity$5 = subseq__5;
return subseq;
})()
;
/**
* sc must be a sorted collection, test(s) one of <, <=, > or
* >=. Returns a reverse seq of those entries with keys ek for
* which (test (.. sc comparator (compare ek key)) 0) is true
*/
cljs.core.rsubseq = (function() {
var rsubseq = null;
var rsubseq__3 = (function (sc,test,key){
var include__9702 = cljs.core.mk_bound_fn.call(null,sc,test,key);
if(cljs.core.truth_(cljs.core.PersistentHashSet.fromArray([cljs.core._LT_,cljs.core._LT__EQ_]).call(null,test)))
{var temp__3974__auto____9703 = cljs.core._sorted_seq_from.call(null,sc,key,false);
if(cljs.core.truth_(temp__3974__auto____9703))
{var vec__9704__9705 = temp__3974__auto____9703;
var e__9706 = cljs.core.nth.call(null,vec__9704__9705,0,null);
var s__9707 = vec__9704__9705;
if(cljs.core.truth_(include__9702.call(null,e__9706)))
{return s__9707;
} else
{return cljs.core.next.call(null,s__9707);
}
} else
{return null;
}
} else
{return cljs.core.take_while.call(null,include__9702,cljs.core._sorted_seq.call(null,sc,false));
}
});
var rsubseq__5 = (function (sc,start_test,start_key,end_test,end_key){
var temp__3974__auto____9708 = cljs.core._sorted_seq_from.call(null,sc,end_key,false);
if(cljs.core.truth_(temp__3974__auto____9708))
{var vec__9709__9710 = temp__3974__auto____9708;
var e__9711 = cljs.core.nth.call(null,vec__9709__9710,0,null);
var s__9712 = vec__9709__9710;
return cljs.core.take_while.call(null,cljs.core.mk_bound_fn.call(null,sc,start_test,start_key),(cljs.core.truth_(cljs.core.mk_bound_fn.call(null,sc,end_test,end_key).call(null,e__9711))?s__9712:cljs.core.next.call(null,s__9712)));
} else
{return null;
}
});
rsubseq = function(sc,start_test,start_key,end_test,end_key){
switch(arguments.length){
case 3:
return rsubseq__3.call(this,sc,start_test,start_key);
case 5:
return rsubseq__5.call(this,sc,start_test,start_key,end_test,end_key);
}
throw('Invalid arity: ' + arguments.length);
};
rsubseq.cljs$lang$arity$3 = rsubseq__3;
rsubseq.cljs$lang$arity$5 = rsubseq__5;
return rsubseq;
})()
;

/**
* @constructor
*/
cljs.core.Range = (function (meta,start,end,step,__hash){
this.meta = meta;
this.start = start;
this.end = end;
this.step = step;
this.__hash = __hash;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 32375006;
})
cljs.core.Range.cljs$lang$type = true;
cljs.core.Range.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/Range");
});
cljs.core.Range.prototype.cljs$core$IHash$_hash$arity$1 = (function (rng){
var this__9713 = this;
var h__2220__auto____9714 = this__9713.__hash;
if(!((h__2220__auto____9714 == null)))
{return h__2220__auto____9714;
} else
{var h__2220__auto____9715 = cljs.core.hash_coll.call(null,rng);
this__9713.__hash = h__2220__auto____9715;
return h__2220__auto____9715;
}
});
cljs.core.Range.prototype.cljs$core$INext$_next$arity$1 = (function (rng){
var this__9716 = this;
if((this__9716.step > 0))
{if(((this__9716.start + this__9716.step) < this__9716.end))
{return (new cljs.core.Range(this__9716.meta,(this__9716.start + this__9716.step),this__9716.end,this__9716.step,null));
} else
{return null;
}
} else
{if(((this__9716.start + this__9716.step) > this__9716.end))
{return (new cljs.core.Range(this__9716.meta,(this__9716.start + this__9716.step),this__9716.end,this__9716.step,null));
} else
{return null;
}
}
});
cljs.core.Range.prototype.cljs$core$ICollection$_conj$arity$2 = (function (rng,o){
var this__9717 = this;
return cljs.core.cons.call(null,o,rng);
});
cljs.core.Range.prototype.toString = (function (){
var this__9718 = this;
var this__9719 = this;
return cljs.core.pr_str.call(null,this__9719);
});
cljs.core.Range.prototype.cljs$core$IReduce$_reduce$arity$2 = (function (rng,f){
var this__9720 = this;
return cljs.core.ci_reduce.call(null,rng,f);
});
cljs.core.Range.prototype.cljs$core$IReduce$_reduce$arity$3 = (function (rng,f,s){
var this__9721 = this;
return cljs.core.ci_reduce.call(null,rng,f,s);
});
cljs.core.Range.prototype.cljs$core$ISeqable$_seq$arity$1 = (function (rng){
var this__9722 = this;
if((this__9722.step > 0))
{if((this__9722.start < this__9722.end))
{return rng;
} else
{return null;
}
} else
{if((this__9722.start > this__9722.end))
{return rng;
} else
{return null;
}
}
});
cljs.core.Range.prototype.cljs$core$ICounted$_count$arity$1 = (function (rng){
var this__9723 = this;
if(cljs.core.not.call(null,rng.cljs$core$ISeqable$_seq$arity$1(rng)))
{return 0;
} else
{return Math.ceil(((this__9723.end - this__9723.start) / this__9723.step));
}
});
cljs.core.Range.prototype.cljs$core$ISeq$_first$arity$1 = (function (rng){
var this__9724 = this;
return this__9724.start;
});
cljs.core.Range.prototype.cljs$core$ISeq$_rest$arity$1 = (function (rng){
var this__9725 = this;
if(!((rng.cljs$core$ISeqable$_seq$arity$1(rng) == null)))
{return (new cljs.core.Range(this__9725.meta,(this__9725.start + this__9725.step),this__9725.end,this__9725.step,null));
} else
{return cljs.core.List.EMPTY;
}
});
cljs.core.Range.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (rng,other){
var this__9726 = this;
return cljs.core.equiv_sequential.call(null,rng,other);
});
cljs.core.Range.prototype.cljs$core$IWithMeta$_with_meta$arity$2 = (function (rng,meta){
var this__9727 = this;
return (new cljs.core.Range(meta,this__9727.start,this__9727.end,this__9727.step,this__9727.__hash));
});
cljs.core.Range.prototype.cljs$core$IMeta$_meta$arity$1 = (function (rng){
var this__9728 = this;
return this__9728.meta;
});
cljs.core.Range.prototype.cljs$core$IIndexed$_nth$arity$2 = (function (rng,n){
var this__9729 = this;
if((n < rng.cljs$core$ICounted$_count$arity$1(rng)))
{return (this__9729.start + (n * this__9729.step));
} else
{if((function (){var and__3822__auto____9730 = (this__9729.start > this__9729.end);
if(and__3822__auto____9730)
{return (this__9729.step === 0);
} else
{return and__3822__auto____9730;
}
})())
{return this__9729.start;
} else
{throw (new Error("Index out of bounds"));
}
}
});
cljs.core.Range.prototype.cljs$core$IIndexed$_nth$arity$3 = (function (rng,n,not_found){
var this__9731 = this;
if((n < rng.cljs$core$ICounted$_count$arity$1(rng)))
{return (this__9731.start + (n * this__9731.step));
} else
{if((function (){var and__3822__auto____9732 = (this__9731.start > this__9731.end);
if(and__3822__auto____9732)
{return (this__9731.step === 0);
} else
{return and__3822__auto____9732;
}
})())
{return this__9731.start;
} else
{return not_found;
}
}
});
cljs.core.Range.prototype.cljs$core$IEmptyableCollection$_empty$arity$1 = (function (rng){
var this__9733 = this;
return cljs.core.with_meta.call(null,cljs.core.List.EMPTY,this__9733.meta);
});
cljs.core.Range;
/**
* Returns a lazy seq of nums from start (inclusive) to end
* (exclusive), by step, where start defaults to 0, step to 1,
* and end to infinity.
*/
cljs.core.range = (function() {
var range = null;
var range__0 = (function (){
return range.call(null,0,Number.MAX_VALUE,1);
});
var range__1 = (function (end){
return range.call(null,0,end,1);
});
var range__2 = (function (start,end){
return range.call(null,start,end,1);
});
var range__3 = (function (start,end,step){
return (new cljs.core.Range(null,start,end,step,null));
});
range = function(start,end,step){
switch(arguments.length){
case 0:
return range__0.call(this);
case 1:
return range__1.call(this,start);
case 2:
return range__2.call(this,start,end);
case 3:
return range__3.call(this,start,end,step);
}
throw('Invalid arity: ' + arguments.length);
};
range.cljs$lang$arity$0 = range__0;
range.cljs$lang$arity$1 = range__1;
range.cljs$lang$arity$2 = range__2;
range.cljs$lang$arity$3 = range__3;
return range;
})()
;
/**
* Returns a lazy seq of every nth item in coll.
*/
cljs.core.take_nth = (function take_nth(n,coll){
return (new cljs.core.LazySeq(null,false,(function (){
var temp__3974__auto____9736 = cljs.core.seq.call(null,coll);
if(temp__3974__auto____9736)
{var s__9737 = temp__3974__auto____9736;
return cljs.core.cons.call(null,cljs.core.first.call(null,s__9737),take_nth.call(null,n,cljs.core.drop.call(null,n,s__9737)));
} else
{return null;
}
}),null));
});
/**
* Returns a vector of [(take-while pred coll) (drop-while pred coll)]
*/
cljs.core.split_with = (function split_with(pred,coll){
return cljs.core.PersistentVector.fromArray([cljs.core.take_while.call(null,pred,coll),cljs.core.drop_while.call(null,pred,coll)], true);
});
/**
* Applies f to each value in coll, splitting it each time f returns
* a new value.  Returns a lazy seq of partitions.
*/
cljs.core.partition_by = (function partition_by(f,coll){
return (new cljs.core.LazySeq(null,false,(function (){
var temp__3974__auto____9744 = cljs.core.seq.call(null,coll);
if(temp__3974__auto____9744)
{var s__9745 = temp__3974__auto____9744;
var fst__9746 = cljs.core.first.call(null,s__9745);
var fv__9747 = f.call(null,fst__9746);
var run__9748 = cljs.core.cons.call(null,fst__9746,cljs.core.take_while.call(null,(function (p1__9738_SHARP_){
return cljs.core._EQ_.call(null,fv__9747,f.call(null,p1__9738_SHARP_));
}),cljs.core.next.call(null,s__9745)));
return cljs.core.cons.call(null,run__9748,partition_by.call(null,f,cljs.core.seq.call(null,cljs.core.drop.call(null,cljs.core.count.call(null,run__9748),s__9745))));
} else
{return null;
}
}),null));
});
/**
* Returns a map from distinct items in coll to the number of times
* they appear.
*/
cljs.core.frequencies = (function frequencies(coll){
return cljs.core.persistent_BANG_.call(null,cljs.core.reduce.call(null,(function (counts,x){
return cljs.core.assoc_BANG_.call(null,counts,x,(cljs.core._lookup.call(null,counts,x,0) + 1));
}),cljs.core.transient$.call(null,cljs.core.ObjMap.EMPTY),coll));
});
/**
* Returns a lazy seq of the intermediate values of the reduction (as
* per reduce) of coll by f, starting with init.
*/
cljs.core.reductions = (function() {
var reductions = null;
var reductions__2 = (function (f,coll){
return (new cljs.core.LazySeq(null,false,(function (){
var temp__3971__auto____9763 = cljs.core.seq.call(null,coll);
if(temp__3971__auto____9763)
{var s__9764 = temp__3971__auto____9763;
return reductions.call(null,f,cljs.core.first.call(null,s__9764),cljs.core.rest.call(null,s__9764));
} else
{return cljs.core.list.call(null,f.call(null));
}
}),null));
});
var reductions__3 = (function (f,init,coll){
return cljs.core.cons.call(null,init,(new cljs.core.LazySeq(null,false,(function (){
var temp__3974__auto____9765 = cljs.core.seq.call(null,coll);
if(temp__3974__auto____9765)
{var s__9766 = temp__3974__auto____9765;
return reductions.call(null,f,f.call(null,init,cljs.core.first.call(null,s__9766)),cljs.core.rest.call(null,s__9766));
} else
{return null;
}
}),null)));
});
reductions = function(f,init,coll){
switch(arguments.length){
case 2:
return reductions__2.call(this,f,init);
case 3:
return reductions__3.call(this,f,init,coll);
}
throw('Invalid arity: ' + arguments.length);
};
reductions.cljs$lang$arity$2 = reductions__2;
reductions.cljs$lang$arity$3 = reductions__3;
return reductions;
})()
;
/**
* Takes a set of functions and returns a fn that is the juxtaposition
* of those fns.  The returned fn takes a variable number of args, and
* returns a vector containing the result of applying each fn to the
* args (left-to-right).
* ((juxt a b c) x) => [(a x) (b x) (c x)]
* @param {...*} var_args
*/
cljs.core.juxt = (function() {
var juxt = null;
var juxt__1 = (function (f){
return (function() {
var G__9769 = null;
var G__9769__0 = (function (){
return cljs.core.vector.call(null,f.call(null));
});
var G__9769__1 = (function (x){
return cljs.core.vector.call(null,f.call(null,x));
});
var G__9769__2 = (function (x,y){
return cljs.core.vector.call(null,f.call(null,x,y));
});
var G__9769__3 = (function (x,y,z){
return cljs.core.vector.call(null,f.call(null,x,y,z));
});
var G__9769__4 = (function() { 
var G__9770__delegate = function (x,y,z,args){
return cljs.core.vector.call(null,cljs.core.apply.call(null,f,x,y,z,args));
};
var G__9770 = function (x,y,z,var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return G__9770__delegate.call(this, x, y, z, args);
};
G__9770.cljs$lang$maxFixedArity = 3;
G__9770.cljs$lang$applyTo = (function (arglist__9771){
var x = cljs.core.first(arglist__9771);
var y = cljs.core.first(cljs.core.next(arglist__9771));
var z = cljs.core.first(cljs.core.next(cljs.core.next(arglist__9771)));
var args = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__9771)));
return G__9770__delegate(x, y, z, args);
});
G__9770.cljs$lang$arity$variadic = G__9770__delegate;
return G__9770;
})()
;
G__9769 = function(x,y,z,var_args){
var args = var_args;
switch(arguments.length){
case 0:
return G__9769__0.call(this);
case 1:
return G__9769__1.call(this,x);
case 2:
return G__9769__2.call(this,x,y);
case 3:
return G__9769__3.call(this,x,y,z);
default:
return G__9769__4.cljs$lang$arity$variadic(x,y,z, cljs.core.array_seq(arguments, 3));
}
throw('Invalid arity: ' + arguments.length);
};
G__9769.cljs$lang$maxFixedArity = 3;
G__9769.cljs$lang$applyTo = G__9769__4.cljs$lang$applyTo;
return G__9769;
})()
});
var juxt__2 = (function (f,g){
return (function() {
var G__9772 = null;
var G__9772__0 = (function (){
return cljs.core.vector.call(null,f.call(null),g.call(null));
});
var G__9772__1 = (function (x){
return cljs.core.vector.call(null,f.call(null,x),g.call(null,x));
});
var G__9772__2 = (function (x,y){
return cljs.core.vector.call(null,f.call(null,x,y),g.call(null,x,y));
});
var G__9772__3 = (function (x,y,z){
return cljs.core.vector.call(null,f.call(null,x,y,z),g.call(null,x,y,z));
});
var G__9772__4 = (function() { 
var G__9773__delegate = function (x,y,z,args){
return cljs.core.vector.call(null,cljs.core.apply.call(null,f,x,y,z,args),cljs.core.apply.call(null,g,x,y,z,args));
};
var G__9773 = function (x,y,z,var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return G__9773__delegate.call(this, x, y, z, args);
};
G__9773.cljs$lang$maxFixedArity = 3;
G__9773.cljs$lang$applyTo = (function (arglist__9774){
var x = cljs.core.first(arglist__9774);
var y = cljs.core.first(cljs.core.next(arglist__9774));
var z = cljs.core.first(cljs.core.next(cljs.core.next(arglist__9774)));
var args = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__9774)));
return G__9773__delegate(x, y, z, args);
});
G__9773.cljs$lang$arity$variadic = G__9773__delegate;
return G__9773;
})()
;
G__9772 = function(x,y,z,var_args){
var args = var_args;
switch(arguments.length){
case 0:
return G__9772__0.call(this);
case 1:
return G__9772__1.call(this,x);
case 2:
return G__9772__2.call(this,x,y);
case 3:
return G__9772__3.call(this,x,y,z);
default:
return G__9772__4.cljs$lang$arity$variadic(x,y,z, cljs.core.array_seq(arguments, 3));
}
throw('Invalid arity: ' + arguments.length);
};
G__9772.cljs$lang$maxFixedArity = 3;
G__9772.cljs$lang$applyTo = G__9772__4.cljs$lang$applyTo;
return G__9772;
})()
});
var juxt__3 = (function (f,g,h){
return (function() {
var G__9775 = null;
var G__9775__0 = (function (){
return cljs.core.vector.call(null,f.call(null),g.call(null),h.call(null));
});
var G__9775__1 = (function (x){
return cljs.core.vector.call(null,f.call(null,x),g.call(null,x),h.call(null,x));
});
var G__9775__2 = (function (x,y){
return cljs.core.vector.call(null,f.call(null,x,y),g.call(null,x,y),h.call(null,x,y));
});
var G__9775__3 = (function (x,y,z){
return cljs.core.vector.call(null,f.call(null,x,y,z),g.call(null,x,y,z),h.call(null,x,y,z));
});
var G__9775__4 = (function() { 
var G__9776__delegate = function (x,y,z,args){
return cljs.core.vector.call(null,cljs.core.apply.call(null,f,x,y,z,args),cljs.core.apply.call(null,g,x,y,z,args),cljs.core.apply.call(null,h,x,y,z,args));
};
var G__9776 = function (x,y,z,var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return G__9776__delegate.call(this, x, y, z, args);
};
G__9776.cljs$lang$maxFixedArity = 3;
G__9776.cljs$lang$applyTo = (function (arglist__9777){
var x = cljs.core.first(arglist__9777);
var y = cljs.core.first(cljs.core.next(arglist__9777));
var z = cljs.core.first(cljs.core.next(cljs.core.next(arglist__9777)));
var args = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__9777)));
return G__9776__delegate(x, y, z, args);
});
G__9776.cljs$lang$arity$variadic = G__9776__delegate;
return G__9776;
})()
;
G__9775 = function(x,y,z,var_args){
var args = var_args;
switch(arguments.length){
case 0:
return G__9775__0.call(this);
case 1:
return G__9775__1.call(this,x);
case 2:
return G__9775__2.call(this,x,y);
case 3:
return G__9775__3.call(this,x,y,z);
default:
return G__9775__4.cljs$lang$arity$variadic(x,y,z, cljs.core.array_seq(arguments, 3));
}
throw('Invalid arity: ' + arguments.length);
};
G__9775.cljs$lang$maxFixedArity = 3;
G__9775.cljs$lang$applyTo = G__9775__4.cljs$lang$applyTo;
return G__9775;
})()
});
var juxt__4 = (function() { 
var G__9778__delegate = function (f,g,h,fs){
var fs__9768 = cljs.core.list_STAR_.call(null,f,g,h,fs);
return (function() {
var G__9779 = null;
var G__9779__0 = (function (){
return cljs.core.reduce.call(null,(function (p1__9749_SHARP_,p2__9750_SHARP_){
return cljs.core.conj.call(null,p1__9749_SHARP_,p2__9750_SHARP_.call(null));
}),cljs.core.PersistentVector.EMPTY,fs__9768);
});
var G__9779__1 = (function (x){
return cljs.core.reduce.call(null,(function (p1__9751_SHARP_,p2__9752_SHARP_){
return cljs.core.conj.call(null,p1__9751_SHARP_,p2__9752_SHARP_.call(null,x));
}),cljs.core.PersistentVector.EMPTY,fs__9768);
});
var G__9779__2 = (function (x,y){
return cljs.core.reduce.call(null,(function (p1__9753_SHARP_,p2__9754_SHARP_){
return cljs.core.conj.call(null,p1__9753_SHARP_,p2__9754_SHARP_.call(null,x,y));
}),cljs.core.PersistentVector.EMPTY,fs__9768);
});
var G__9779__3 = (function (x,y,z){
return cljs.core.reduce.call(null,(function (p1__9755_SHARP_,p2__9756_SHARP_){
return cljs.core.conj.call(null,p1__9755_SHARP_,p2__9756_SHARP_.call(null,x,y,z));
}),cljs.core.PersistentVector.EMPTY,fs__9768);
});
var G__9779__4 = (function() { 
var G__9780__delegate = function (x,y,z,args){
return cljs.core.reduce.call(null,(function (p1__9757_SHARP_,p2__9758_SHARP_){
return cljs.core.conj.call(null,p1__9757_SHARP_,cljs.core.apply.call(null,p2__9758_SHARP_,x,y,z,args));
}),cljs.core.PersistentVector.EMPTY,fs__9768);
};
var G__9780 = function (x,y,z,var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return G__9780__delegate.call(this, x, y, z, args);
};
G__9780.cljs$lang$maxFixedArity = 3;
G__9780.cljs$lang$applyTo = (function (arglist__9781){
var x = cljs.core.first(arglist__9781);
var y = cljs.core.first(cljs.core.next(arglist__9781));
var z = cljs.core.first(cljs.core.next(cljs.core.next(arglist__9781)));
var args = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__9781)));
return G__9780__delegate(x, y, z, args);
});
G__9780.cljs$lang$arity$variadic = G__9780__delegate;
return G__9780;
})()
;
G__9779 = function(x,y,z,var_args){
var args = var_args;
switch(arguments.length){
case 0:
return G__9779__0.call(this);
case 1:
return G__9779__1.call(this,x);
case 2:
return G__9779__2.call(this,x,y);
case 3:
return G__9779__3.call(this,x,y,z);
default:
return G__9779__4.cljs$lang$arity$variadic(x,y,z, cljs.core.array_seq(arguments, 3));
}
throw('Invalid arity: ' + arguments.length);
};
G__9779.cljs$lang$maxFixedArity = 3;
G__9779.cljs$lang$applyTo = G__9779__4.cljs$lang$applyTo;
return G__9779;
})()
};
var G__9778 = function (f,g,h,var_args){
var fs = null;
if (goog.isDef(var_args)) {
  fs = cljs.core.array_seq(Array.prototype.slice.call(arguments, 3),0);
} 
return G__9778__delegate.call(this, f, g, h, fs);
};
G__9778.cljs$lang$maxFixedArity = 3;
G__9778.cljs$lang$applyTo = (function (arglist__9782){
var f = cljs.core.first(arglist__9782);
var g = cljs.core.first(cljs.core.next(arglist__9782));
var h = cljs.core.first(cljs.core.next(cljs.core.next(arglist__9782)));
var fs = cljs.core.rest(cljs.core.next(cljs.core.next(arglist__9782)));
return G__9778__delegate(f, g, h, fs);
});
G__9778.cljs$lang$arity$variadic = G__9778__delegate;
return G__9778;
})()
;
juxt = function(f,g,h,var_args){
var fs = var_args;
switch(arguments.length){
case 1:
return juxt__1.call(this,f);
case 2:
return juxt__2.call(this,f,g);
case 3:
return juxt__3.call(this,f,g,h);
default:
return juxt__4.cljs$lang$arity$variadic(f,g,h, cljs.core.array_seq(arguments, 3));
}
throw('Invalid arity: ' + arguments.length);
};
juxt.cljs$lang$maxFixedArity = 3;
juxt.cljs$lang$applyTo = juxt__4.cljs$lang$applyTo;
juxt.cljs$lang$arity$1 = juxt__1;
juxt.cljs$lang$arity$2 = juxt__2;
juxt.cljs$lang$arity$3 = juxt__3;
juxt.cljs$lang$arity$variadic = juxt__4.cljs$lang$arity$variadic;
return juxt;
})()
;
/**
* When lazy sequences are produced via functions that have side
* effects, any effects other than those needed to produce the first
* element in the seq do not occur until the seq is consumed. dorun can
* be used to force any effects. Walks through the successive nexts of
* the seq, does not retain the head and returns nil.
*/
cljs.core.dorun = (function() {
var dorun = null;
var dorun__1 = (function (coll){
while(true){
if(cljs.core.seq.call(null,coll))
{{
var G__9785 = cljs.core.next.call(null,coll);
coll = G__9785;
continue;
}
} else
{return null;
}
break;
}
});
var dorun__2 = (function (n,coll){
while(true){
if(cljs.core.truth_((function (){var and__3822__auto____9784 = cljs.core.seq.call(null,coll);
if(and__3822__auto____9784)
{return (n > 0);
} else
{return and__3822__auto____9784;
}
})()))
{{
var G__9786 = (n - 1);
var G__9787 = cljs.core.next.call(null,coll);
n = G__9786;
coll = G__9787;
continue;
}
} else
{return null;
}
break;
}
});
dorun = function(n,coll){
switch(arguments.length){
case 1:
return dorun__1.call(this,n);
case 2:
return dorun__2.call(this,n,coll);
}
throw('Invalid arity: ' + arguments.length);
};
dorun.cljs$lang$arity$1 = dorun__1;
dorun.cljs$lang$arity$2 = dorun__2;
return dorun;
})()
;
/**
* When lazy sequences are produced via functions that have side
* effects, any effects other than those needed to produce the first
* element in the seq do not occur until the seq is consumed. doall can
* be used to force any effects. Walks through the successive nexts of
* the seq, retains the head and returns it, thus causing the entire
* seq to reside in memory at one time.
*/
cljs.core.doall = (function() {
var doall = null;
var doall__1 = (function (coll){
cljs.core.dorun.call(null,coll);
return coll;
});
var doall__2 = (function (n,coll){
cljs.core.dorun.call(null,n,coll);
return coll;
});
doall = function(n,coll){
switch(arguments.length){
case 1:
return doall__1.call(this,n);
case 2:
return doall__2.call(this,n,coll);
}
throw('Invalid arity: ' + arguments.length);
};
doall.cljs$lang$arity$1 = doall__1;
doall.cljs$lang$arity$2 = doall__2;
return doall;
})()
;
cljs.core.regexp_QMARK_ = (function regexp_QMARK_(o){
return o instanceof RegExp;
});
/**
* Returns the result of (re-find re s) if re fully matches s.
*/
cljs.core.re_matches = (function re_matches(re,s){
var matches__9789 = re.exec(s);
if(cljs.core._EQ_.call(null,cljs.core.first.call(null,matches__9789),s))
{if((cljs.core.count.call(null,matches__9789) === 1))
{return cljs.core.first.call(null,matches__9789);
} else
{return cljs.core.vec.call(null,matches__9789);
}
} else
{return null;
}
});
/**
* Returns the first regex match, if any, of s to re, using
* re.exec(s). Returns a vector, containing first the matching
* substring, then any capturing groups if the regular expression contains
* capturing groups.
*/
cljs.core.re_find = (function re_find(re,s){
var matches__9791 = re.exec(s);
if((matches__9791 == null))
{return null;
} else
{if((cljs.core.count.call(null,matches__9791) === 1))
{return cljs.core.first.call(null,matches__9791);
} else
{return cljs.core.vec.call(null,matches__9791);
}
}
});
/**
* Returns a lazy sequence of successive matches of re in s.
*/
cljs.core.re_seq = (function re_seq(re,s){
var match_data__9796 = cljs.core.re_find.call(null,re,s);
var match_idx__9797 = s.search(re);
var match_str__9798 = ((cljs.core.coll_QMARK_.call(null,match_data__9796))?cljs.core.first.call(null,match_data__9796):match_data__9796);
var post_match__9799 = cljs.core.subs.call(null,s,(match_idx__9797 + cljs.core.count.call(null,match_str__9798)));
if(cljs.core.truth_(match_data__9796))
{return (new cljs.core.LazySeq(null,false,(function (){
return cljs.core.cons.call(null,match_data__9796,re_seq.call(null,re,post_match__9799));
}),null));
} else
{return null;
}
});
/**
* Returns an instance of RegExp which has compiled the provided string.
*/
cljs.core.re_pattern = (function re_pattern(s){
var vec__9806__9807 = cljs.core.re_find.call(null,/^(?:\(\?([idmsux]*)\))?(.*)/,s);
var ___9808 = cljs.core.nth.call(null,vec__9806__9807,0,null);
var flags__9809 = cljs.core.nth.call(null,vec__9806__9807,1,null);
var pattern__9810 = cljs.core.nth.call(null,vec__9806__9807,2,null);
return (new RegExp(pattern__9810,flags__9809));
});
cljs.core.pr_sequential = (function pr_sequential(print_one,begin,sep,end,opts,coll){
return cljs.core.concat.call(null,cljs.core.PersistentVector.fromArray([begin], true),cljs.core.flatten1.call(null,cljs.core.interpose.call(null,cljs.core.PersistentVector.fromArray([sep], true),cljs.core.map.call(null,(function (p1__9800_SHARP_){
return print_one.call(null,p1__9800_SHARP_,opts);
}),coll))),cljs.core.PersistentVector.fromArray([end], true));
});
cljs.core.string_print = (function string_print(x){
cljs.core._STAR_print_fn_STAR_.call(null,x);
return null;
});
cljs.core.flush = (function flush(){
return null;
});
cljs.core.pr_seq = (function pr_seq(obj,opts){
if((obj == null))
{return cljs.core.list.call(null,"nil");
} else
{if((void 0 === obj))
{return cljs.core.list.call(null,"#<undefined>");
} else
{if("\uFDD0'else")
{return cljs.core.concat.call(null,(cljs.core.truth_((function (){var and__3822__auto____9820 = cljs.core._lookup.call(null,opts,"\uFDD0'meta",null);
if(cljs.core.truth_(and__3822__auto____9820))
{var and__3822__auto____9824 = (function (){var G__9821__9822 = obj;
if(G__9821__9822)
{if((function (){var or__3824__auto____9823 = (G__9821__9822.cljs$lang$protocol_mask$partition0$ & 131072);
if(or__3824__auto____9823)
{return or__3824__auto____9823;
} else
{return G__9821__9822.cljs$core$IMeta$;
}
})())
{return true;
} else
{if((!G__9821__9822.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.IMeta,G__9821__9822);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.IMeta,G__9821__9822);
}
})();
if(cljs.core.truth_(and__3822__auto____9824))
{return cljs.core.meta.call(null,obj);
} else
{return and__3822__auto____9824;
}
} else
{return and__3822__auto____9820;
}
})())?cljs.core.concat.call(null,cljs.core.PersistentVector.fromArray(["^"], true),pr_seq.call(null,cljs.core.meta.call(null,obj),opts),cljs.core.PersistentVector.fromArray([" "], true)):null),(((function (){var and__3822__auto____9825 = !((obj == null));
if(and__3822__auto____9825)
{return obj.cljs$lang$type;
} else
{return and__3822__auto____9825;
}
})())?obj.cljs$lang$ctorPrSeq(obj):(((function (){var G__9826__9827 = obj;
if(G__9826__9827)
{if((function (){var or__3824__auto____9828 = (G__9826__9827.cljs$lang$protocol_mask$partition0$ & 536870912);
if(or__3824__auto____9828)
{return or__3824__auto____9828;
} else
{return G__9826__9827.cljs$core$IPrintable$;
}
})())
{return true;
} else
{if((!G__9826__9827.cljs$lang$protocol_mask$partition0$))
{return cljs.core.type_satisfies_.call(null,cljs.core.IPrintable,G__9826__9827);
} else
{return false;
}
}
} else
{return cljs.core.type_satisfies_.call(null,cljs.core.IPrintable,G__9826__9827);
}
})())?cljs.core._pr_seq.call(null,obj,opts):(cljs.core.truth_(cljs.core.regexp_QMARK_.call(null,obj))?cljs.core.list.call(null,"#\"",obj.source,"\""):(("\uFDD0'else")?cljs.core.list.call(null,"#<",[cljs.core.str(obj)].join(''),">"):null)))));
} else
{return null;
}
}
}
});
cljs.core.pr_sb = (function pr_sb(objs,opts){
var sb__9848 = (new goog.string.StringBuffer());
var G__9849__9850 = cljs.core.seq.call(null,cljs.core.pr_seq.call(null,cljs.core.first.call(null,objs),opts));
if(G__9849__9850)
{var string__9851 = cljs.core.first.call(null,G__9849__9850);
var G__9849__9852 = G__9849__9850;
while(true){
sb__9848.append(string__9851);
var temp__3974__auto____9853 = cljs.core.next.call(null,G__9849__9852);
if(temp__3974__auto____9853)
{var G__9849__9854 = temp__3974__auto____9853;
{
var G__9867 = cljs.core.first.call(null,G__9849__9854);
var G__9868 = G__9849__9854;
string__9851 = G__9867;
G__9849__9852 = G__9868;
continue;
}
} else
{}
break;
}
} else
{}
var G__9855__9856 = cljs.core.seq.call(null,cljs.core.next.call(null,objs));
if(G__9855__9856)
{var obj__9857 = cljs.core.first.call(null,G__9855__9856);
var G__9855__9858 = G__9855__9856;
while(true){
sb__9848.append(" ");
var G__9859__9860 = cljs.core.seq.call(null,cljs.core.pr_seq.call(null,obj__9857,opts));
if(G__9859__9860)
{var string__9861 = cljs.core.first.call(null,G__9859__9860);
var G__9859__9862 = G__9859__9860;
while(true){
sb__9848.append(string__9861);
var temp__3974__auto____9863 = cljs.core.next.call(null,G__9859__9862);
if(temp__3974__auto____9863)
{var G__9859__9864 = temp__3974__auto____9863;
{
var G__9869 = cljs.core.first.call(null,G__9859__9864);
var G__9870 = G__9859__9864;
string__9861 = G__9869;
G__9859__9862 = G__9870;
continue;
}
} else
{}
break;
}
} else
{}
var temp__3974__auto____9865 = cljs.core.next.call(null,G__9855__9858);
if(temp__3974__auto____9865)
{var G__9855__9866 = temp__3974__auto____9865;
{
var G__9871 = cljs.core.first.call(null,G__9855__9866);
var G__9872 = G__9855__9866;
obj__9857 = G__9871;
G__9855__9858 = G__9872;
continue;
}
} else
{}
break;
}
} else
{}
return sb__9848;
});
/**
* Prints a sequence of objects to a string, observing all the
* options given in opts
*/
cljs.core.pr_str_with_opts = (function pr_str_with_opts(objs,opts){
return [cljs.core.str(cljs.core.pr_sb.call(null,objs,opts))].join('');
});
/**
* Same as pr-str-with-opts followed by (newline)
*/
cljs.core.prn_str_with_opts = (function prn_str_with_opts(objs,opts){
var sb__9874 = cljs.core.pr_sb.call(null,objs,opts);
sb__9874.append("\n");
return [cljs.core.str(sb__9874)].join('');
});
/**
* Prints a sequence of objects using string-print, observing all
* the options given in opts
*/
cljs.core.pr_with_opts = (function pr_with_opts(objs,opts){
var G__9893__9894 = cljs.core.seq.call(null,cljs.core.pr_seq.call(null,cljs.core.first.call(null,objs),opts));
if(G__9893__9894)
{var string__9895 = cljs.core.first.call(null,G__9893__9894);
var G__9893__9896 = G__9893__9894;
while(true){
cljs.core.string_print.call(null,string__9895);
var temp__3974__auto____9897 = cljs.core.next.call(null,G__9893__9896);
if(temp__3974__auto____9897)
{var G__9893__9898 = temp__3974__auto____9897;
{
var G__9911 = cljs.core.first.call(null,G__9893__9898);
var G__9912 = G__9893__9898;
string__9895 = G__9911;
G__9893__9896 = G__9912;
continue;
}
} else
{}
break;
}
} else
{}
var G__9899__9900 = cljs.core.seq.call(null,cljs.core.next.call(null,objs));
if(G__9899__9900)
{var obj__9901 = cljs.core.first.call(null,G__9899__9900);
var G__9899__9902 = G__9899__9900;
while(true){
cljs.core.string_print.call(null," ");
var G__9903__9904 = cljs.core.seq.call(null,cljs.core.pr_seq.call(null,obj__9901,opts));
if(G__9903__9904)
{var string__9905 = cljs.core.first.call(null,G__9903__9904);
var G__9903__9906 = G__9903__9904;
while(true){
cljs.core.string_print.call(null,string__9905);
var temp__3974__auto____9907 = cljs.core.next.call(null,G__9903__9906);
if(temp__3974__auto____9907)
{var G__9903__9908 = temp__3974__auto____9907;
{
var G__9913 = cljs.core.first.call(null,G__9903__9908);
var G__9914 = G__9903__9908;
string__9905 = G__9913;
G__9903__9906 = G__9914;
continue;
}
} else
{}
break;
}
} else
{}
var temp__3974__auto____9909 = cljs.core.next.call(null,G__9899__9902);
if(temp__3974__auto____9909)
{var G__9899__9910 = temp__3974__auto____9909;
{
var G__9915 = cljs.core.first.call(null,G__9899__9910);
var G__9916 = G__9899__9910;
obj__9901 = G__9915;
G__9899__9902 = G__9916;
continue;
}
} else
{return null;
}
break;
}
} else
{return null;
}
});
cljs.core.newline = (function newline(opts){
cljs.core.string_print.call(null,"\n");
if(cljs.core.truth_(cljs.core._lookup.call(null,opts,"\uFDD0'flush-on-newline",null)))
{return cljs.core.flush.call(null);
} else
{return null;
}
});
cljs.core._STAR_flush_on_newline_STAR_ = true;
cljs.core._STAR_print_readably_STAR_ = true;
cljs.core._STAR_print_meta_STAR_ = false;
cljs.core._STAR_print_dup_STAR_ = false;
cljs.core.pr_opts = (function pr_opts(){
return cljs.core.ObjMap.fromObject(["\uFDD0'flush-on-newline","\uFDD0'readably","\uFDD0'meta","\uFDD0'dup"],{"\uFDD0'flush-on-newline":cljs.core._STAR_flush_on_newline_STAR_,"\uFDD0'readably":cljs.core._STAR_print_readably_STAR_,"\uFDD0'meta":cljs.core._STAR_print_meta_STAR_,"\uFDD0'dup":cljs.core._STAR_print_dup_STAR_});
});
/**
* pr to a string, returning it. Fundamental entrypoint to IPrintable.
* @param {...*} var_args
*/
cljs.core.pr_str = (function() { 
var pr_str__delegate = function (objs){
return cljs.core.pr_str_with_opts.call(null,objs,cljs.core.pr_opts.call(null));
};
var pr_str = function (var_args){
var objs = null;
if (goog.isDef(var_args)) {
  objs = cljs.core.array_seq(Array.prototype.slice.call(arguments, 0),0);
} 
return pr_str__delegate.call(this, objs);
};
pr_str.cljs$lang$maxFixedArity = 0;
pr_str.cljs$lang$applyTo = (function (arglist__9917){
var objs = cljs.core.seq(arglist__9917);;
return pr_str__delegate(objs);
});
pr_str.cljs$lang$arity$variadic = pr_str__delegate;
return pr_str;
})()
;
/**
* Same as pr-str followed by (newline)
* @param {...*} var_args
*/
cljs.core.prn_str = (function() { 
var prn_str__delegate = function (objs){
return cljs.core.prn_str_with_opts.call(null,objs,cljs.core.pr_opts.call(null));
};
var prn_str = function (var_args){
var objs = null;
if (goog.isDef(var_args)) {
  objs = cljs.core.array_seq(Array.prototype.slice.call(arguments, 0),0);
} 
return prn_str__delegate.call(this, objs);
};
prn_str.cljs$lang$maxFixedArity = 0;
prn_str.cljs$lang$applyTo = (function (arglist__9918){
var objs = cljs.core.seq(arglist__9918);;
return prn_str__delegate(objs);
});
prn_str.cljs$lang$arity$variadic = prn_str__delegate;
return prn_str;
})()
;
/**
* Prints the object(s) using string-print.  Prints the
* object(s), separated by spaces if there is more than one.
* By default, pr and prn print in a way that objects can be
* read by the reader
* @param {...*} var_args
*/
cljs.core.pr = (function() { 
var pr__delegate = function (objs){
return cljs.core.pr_with_opts.call(null,objs,cljs.core.pr_opts.call(null));
};
var pr = function (var_args){
var objs = null;
if (goog.isDef(var_args)) {
  objs = cljs.core.array_seq(Array.prototype.slice.call(arguments, 0),0);
} 
return pr__delegate.call(this, objs);
};
pr.cljs$lang$maxFixedArity = 0;
pr.cljs$lang$applyTo = (function (arglist__9919){
var objs = cljs.core.seq(arglist__9919);;
return pr__delegate(objs);
});
pr.cljs$lang$arity$variadic = pr__delegate;
return pr;
})()
;
/**
* Prints the object(s) using string-print.
* print and println produce output for human consumption.
* @param {...*} var_args
*/
cljs.core.print = (function() { 
var cljs_core_print__delegate = function (objs){
return cljs.core.pr_with_opts.call(null,objs,cljs.core.assoc.call(null,cljs.core.pr_opts.call(null),"\uFDD0'readably",false));
};
var cljs_core_print = function (var_args){
var objs = null;
if (goog.isDef(var_args)) {
  objs = cljs.core.array_seq(Array.prototype.slice.call(arguments, 0),0);
} 
return cljs_core_print__delegate.call(this, objs);
};
cljs_core_print.cljs$lang$maxFixedArity = 0;
cljs_core_print.cljs$lang$applyTo = (function (arglist__9920){
var objs = cljs.core.seq(arglist__9920);;
return cljs_core_print__delegate(objs);
});
cljs_core_print.cljs$lang$arity$variadic = cljs_core_print__delegate;
return cljs_core_print;
})()
;
/**
* print to a string, returning it
* @param {...*} var_args
*/
cljs.core.print_str = (function() { 
var print_str__delegate = function (objs){
return cljs.core.pr_str_with_opts.call(null,objs,cljs.core.assoc.call(null,cljs.core.pr_opts.call(null),"\uFDD0'readably",false));
};
var print_str = function (var_args){
var objs = null;
if (goog.isDef(var_args)) {
  objs = cljs.core.array_seq(Array.prototype.slice.call(arguments, 0),0);
} 
return print_str__delegate.call(this, objs);
};
print_str.cljs$lang$maxFixedArity = 0;
print_str.cljs$lang$applyTo = (function (arglist__9921){
var objs = cljs.core.seq(arglist__9921);;
return print_str__delegate(objs);
});
print_str.cljs$lang$arity$variadic = print_str__delegate;
return print_str;
})()
;
/**
* Same as print followed by (newline)
* @param {...*} var_args
*/
cljs.core.println = (function() { 
var println__delegate = function (objs){
cljs.core.pr_with_opts.call(null,objs,cljs.core.assoc.call(null,cljs.core.pr_opts.call(null),"\uFDD0'readably",false));
return cljs.core.newline.call(null,cljs.core.pr_opts.call(null));
};
var println = function (var_args){
var objs = null;
if (goog.isDef(var_args)) {
  objs = cljs.core.array_seq(Array.prototype.slice.call(arguments, 0),0);
} 
return println__delegate.call(this, objs);
};
println.cljs$lang$maxFixedArity = 0;
println.cljs$lang$applyTo = (function (arglist__9922){
var objs = cljs.core.seq(arglist__9922);;
return println__delegate(objs);
});
println.cljs$lang$arity$variadic = println__delegate;
return println;
})()
;
/**
* println to a string, returning it
* @param {...*} var_args
*/
cljs.core.println_str = (function() { 
var println_str__delegate = function (objs){
return cljs.core.prn_str_with_opts.call(null,objs,cljs.core.assoc.call(null,cljs.core.pr_opts.call(null),"\uFDD0'readably",false));
};
var println_str = function (var_args){
var objs = null;
if (goog.isDef(var_args)) {
  objs = cljs.core.array_seq(Array.prototype.slice.call(arguments, 0),0);
} 
return println_str__delegate.call(this, objs);
};
println_str.cljs$lang$maxFixedArity = 0;
println_str.cljs$lang$applyTo = (function (arglist__9923){
var objs = cljs.core.seq(arglist__9923);;
return println_str__delegate(objs);
});
println_str.cljs$lang$arity$variadic = println_str__delegate;
return println_str;
})()
;
/**
* Same as pr followed by (newline).
* @param {...*} var_args
*/
cljs.core.prn = (function() { 
var prn__delegate = function (objs){
cljs.core.pr_with_opts.call(null,objs,cljs.core.pr_opts.call(null));
return cljs.core.newline.call(null,cljs.core.pr_opts.call(null));
};
var prn = function (var_args){
var objs = null;
if (goog.isDef(var_args)) {
  objs = cljs.core.array_seq(Array.prototype.slice.call(arguments, 0),0);
} 
return prn__delegate.call(this, objs);
};
prn.cljs$lang$maxFixedArity = 0;
prn.cljs$lang$applyTo = (function (arglist__9924){
var objs = cljs.core.seq(arglist__9924);;
return prn__delegate(objs);
});
prn.cljs$lang$arity$variadic = prn__delegate;
return prn;
})()
;
/**
* Prints formatted output, as per format
* @param {...*} var_args
*/
cljs.core.printf = (function() { 
var printf__delegate = function (fmt,args){
return cljs.core.print.call(null,cljs.core.apply.call(null,cljs.core.format,fmt,args));
};
var printf = function (fmt,var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 1),0);
} 
return printf__delegate.call(this, fmt, args);
};
printf.cljs$lang$maxFixedArity = 1;
printf.cljs$lang$applyTo = (function (arglist__9925){
var fmt = cljs.core.first(arglist__9925);
var args = cljs.core.rest(arglist__9925);
return printf__delegate(fmt, args);
});
printf.cljs$lang$arity$variadic = printf__delegate;
return printf;
})()
;
cljs.core.HashMap.prototype.cljs$core$IPrintable$ = true;
cljs.core.HashMap.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (coll,opts){
var pr_pair__9926 = (function (keyval){
return cljs.core.pr_sequential.call(null,cljs.core.pr_seq,""," ","",opts,keyval);
});
return cljs.core.pr_sequential.call(null,pr_pair__9926,"{",", ","}",opts,coll);
});
(cljs.core.IPrintable["number"] = true);
(cljs.core._pr_seq["number"] = (function (n,opts){
return cljs.core.list.call(null,[cljs.core.str(n)].join(''));
}));
cljs.core.IndexedSeq.prototype.cljs$core$IPrintable$ = true;
cljs.core.IndexedSeq.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (coll,opts){
return cljs.core.pr_sequential.call(null,cljs.core.pr_seq,"("," ",")",opts,coll);
});
cljs.core.Subvec.prototype.cljs$core$IPrintable$ = true;
cljs.core.Subvec.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (coll,opts){
return cljs.core.pr_sequential.call(null,cljs.core.pr_seq,"["," ","]",opts,coll);
});
cljs.core.ChunkedCons.prototype.cljs$core$IPrintable$ = true;
cljs.core.ChunkedCons.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (coll,opts){
return cljs.core.pr_sequential.call(null,cljs.core.pr_seq,"("," ",")",opts,coll);
});
cljs.core.PersistentTreeMap.prototype.cljs$core$IPrintable$ = true;
cljs.core.PersistentTreeMap.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (coll,opts){
var pr_pair__9927 = (function (keyval){
return cljs.core.pr_sequential.call(null,cljs.core.pr_seq,""," ","",opts,keyval);
});
return cljs.core.pr_sequential.call(null,pr_pair__9927,"{",", ","}",opts,coll);
});
cljs.core.PersistentArrayMap.prototype.cljs$core$IPrintable$ = true;
cljs.core.PersistentArrayMap.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (coll,opts){
var pr_pair__9928 = (function (keyval){
return cljs.core.pr_sequential.call(null,cljs.core.pr_seq,""," ","",opts,keyval);
});
return cljs.core.pr_sequential.call(null,pr_pair__9928,"{",", ","}",opts,coll);
});
cljs.core.PersistentQueue.prototype.cljs$core$IPrintable$ = true;
cljs.core.PersistentQueue.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (coll,opts){
return cljs.core.pr_sequential.call(null,cljs.core.pr_seq,"#queue ["," ","]",opts,cljs.core.seq.call(null,coll));
});
cljs.core.LazySeq.prototype.cljs$core$IPrintable$ = true;
cljs.core.LazySeq.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (coll,opts){
return cljs.core.pr_sequential.call(null,cljs.core.pr_seq,"("," ",")",opts,coll);
});
cljs.core.RSeq.prototype.cljs$core$IPrintable$ = true;
cljs.core.RSeq.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (coll,opts){
return cljs.core.pr_sequential.call(null,cljs.core.pr_seq,"("," ",")",opts,coll);
});
cljs.core.PersistentTreeSet.prototype.cljs$core$IPrintable$ = true;
cljs.core.PersistentTreeSet.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (coll,opts){
return cljs.core.pr_sequential.call(null,cljs.core.pr_seq,"#{"," ","}",opts,coll);
});
(cljs.core.IPrintable["boolean"] = true);
(cljs.core._pr_seq["boolean"] = (function (bool,opts){
return cljs.core.list.call(null,[cljs.core.str(bool)].join(''));
}));
(cljs.core.IPrintable["string"] = true);
(cljs.core._pr_seq["string"] = (function (obj,opts){
if(cljs.core.keyword_QMARK_.call(null,obj))
{return cljs.core.list.call(null,[cljs.core.str(":"),cljs.core.str((function (){var temp__3974__auto____9929 = cljs.core.namespace.call(null,obj);
if(cljs.core.truth_(temp__3974__auto____9929))
{var nspc__9930 = temp__3974__auto____9929;
return [cljs.core.str(nspc__9930),cljs.core.str("/")].join('');
} else
{return null;
}
})()),cljs.core.str(cljs.core.name.call(null,obj))].join(''));
} else
{if(cljs.core.symbol_QMARK_.call(null,obj))
{return cljs.core.list.call(null,[cljs.core.str((function (){var temp__3974__auto____9931 = cljs.core.namespace.call(null,obj);
if(cljs.core.truth_(temp__3974__auto____9931))
{var nspc__9932 = temp__3974__auto____9931;
return [cljs.core.str(nspc__9932),cljs.core.str("/")].join('');
} else
{return null;
}
})()),cljs.core.str(cljs.core.name.call(null,obj))].join(''));
} else
{if("\uFDD0'else")
{return cljs.core.list.call(null,(cljs.core.truth_((new cljs.core.Keyword("\uFDD0'readably")).call(null,opts))?goog.string.quote(obj):obj));
} else
{return null;
}
}
}
}));
cljs.core.NodeSeq.prototype.cljs$core$IPrintable$ = true;
cljs.core.NodeSeq.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (coll,opts){
return cljs.core.pr_sequential.call(null,cljs.core.pr_seq,"("," ",")",opts,coll);
});
cljs.core.RedNode.prototype.cljs$core$IPrintable$ = true;
cljs.core.RedNode.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (coll,opts){
return cljs.core.pr_sequential.call(null,cljs.core.pr_seq,"["," ","]",opts,coll);
});
cljs.core.ChunkedSeq.prototype.cljs$core$IPrintable$ = true;
cljs.core.ChunkedSeq.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (coll,opts){
return cljs.core.pr_sequential.call(null,cljs.core.pr_seq,"("," ",")",opts,coll);
});
cljs.core.PersistentHashMap.prototype.cljs$core$IPrintable$ = true;
cljs.core.PersistentHashMap.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (coll,opts){
var pr_pair__9933 = (function (keyval){
return cljs.core.pr_sequential.call(null,cljs.core.pr_seq,""," ","",opts,keyval);
});
return cljs.core.pr_sequential.call(null,pr_pair__9933,"{",", ","}",opts,coll);
});
cljs.core.Vector.prototype.cljs$core$IPrintable$ = true;
cljs.core.Vector.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (coll,opts){
return cljs.core.pr_sequential.call(null,cljs.core.pr_seq,"["," ","]",opts,coll);
});
cljs.core.PersistentHashSet.prototype.cljs$core$IPrintable$ = true;
cljs.core.PersistentHashSet.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (coll,opts){
return cljs.core.pr_sequential.call(null,cljs.core.pr_seq,"#{"," ","}",opts,coll);
});
cljs.core.PersistentVector.prototype.cljs$core$IPrintable$ = true;
cljs.core.PersistentVector.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (coll,opts){
return cljs.core.pr_sequential.call(null,cljs.core.pr_seq,"["," ","]",opts,coll);
});
cljs.core.List.prototype.cljs$core$IPrintable$ = true;
cljs.core.List.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (coll,opts){
return cljs.core.pr_sequential.call(null,cljs.core.pr_seq,"("," ",")",opts,coll);
});
(cljs.core.IPrintable["array"] = true);
(cljs.core._pr_seq["array"] = (function (a,opts){
return cljs.core.pr_sequential.call(null,cljs.core.pr_seq,"#<Array [",", ","]>",opts,a);
}));
(cljs.core.IPrintable["function"] = true);
(cljs.core._pr_seq["function"] = (function (this$){
return cljs.core.list.call(null,"#<",[cljs.core.str(this$)].join(''),">");
}));
cljs.core.EmptyList.prototype.cljs$core$IPrintable$ = true;
cljs.core.EmptyList.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (coll,opts){
return cljs.core.list.call(null,"()");
});
cljs.core.BlackNode.prototype.cljs$core$IPrintable$ = true;
cljs.core.BlackNode.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (coll,opts){
return cljs.core.pr_sequential.call(null,cljs.core.pr_seq,"["," ","]",opts,coll);
});
Date.prototype.cljs$core$IPrintable$ = true;
Date.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (d,_){
var normalize__9935 = (function (n,len){
var ns__9934 = [cljs.core.str(n)].join('');
while(true){
if((cljs.core.count.call(null,ns__9934) < len))
{{
var G__9937 = [cljs.core.str("0"),cljs.core.str(ns__9934)].join('');
ns__9934 = G__9937;
continue;
}
} else
{return ns__9934;
}
break;
}
});
return cljs.core.list.call(null,[cljs.core.str("#inst \""),cljs.core.str(d.getUTCFullYear()),cljs.core.str("-"),cljs.core.str(normalize__9935.call(null,(d.getUTCMonth() + 1),2)),cljs.core.str("-"),cljs.core.str(normalize__9935.call(null,d.getUTCDate(),2)),cljs.core.str("T"),cljs.core.str(normalize__9935.call(null,d.getUTCHours(),2)),cljs.core.str(":"),cljs.core.str(normalize__9935.call(null,d.getUTCMinutes(),2)),cljs.core.str(":"),cljs.core.str(normalize__9935.call(null,d.getUTCSeconds(),2)),cljs.core.str("."),cljs.core.str(normalize__9935.call(null,d.getUTCMilliseconds(),3)),cljs.core.str("-"),cljs.core.str("00:00\"")].join(''));
});
cljs.core.Cons.prototype.cljs$core$IPrintable$ = true;
cljs.core.Cons.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (coll,opts){
return cljs.core.pr_sequential.call(null,cljs.core.pr_seq,"("," ",")",opts,coll);
});
cljs.core.Range.prototype.cljs$core$IPrintable$ = true;
cljs.core.Range.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (coll,opts){
return cljs.core.pr_sequential.call(null,cljs.core.pr_seq,"("," ",")",opts,coll);
});
cljs.core.ArrayNodeSeq.prototype.cljs$core$IPrintable$ = true;
cljs.core.ArrayNodeSeq.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (coll,opts){
return cljs.core.pr_sequential.call(null,cljs.core.pr_seq,"("," ",")",opts,coll);
});
cljs.core.ObjMap.prototype.cljs$core$IPrintable$ = true;
cljs.core.ObjMap.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (coll,opts){
var pr_pair__9936 = (function (keyval){
return cljs.core.pr_sequential.call(null,cljs.core.pr_seq,""," ","",opts,keyval);
});
return cljs.core.pr_sequential.call(null,pr_pair__9936,"{",", ","}",opts,coll);
});
cljs.core.PersistentTreeMapSeq.prototype.cljs$core$IPrintable$ = true;
cljs.core.PersistentTreeMapSeq.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (coll,opts){
return cljs.core.pr_sequential.call(null,cljs.core.pr_seq,"("," ",")",opts,coll);
});
cljs.core.PersistentVector.prototype.cljs$core$IComparable$ = true;
cljs.core.PersistentVector.prototype.cljs$core$IComparable$_compare$arity$2 = (function (x,y){
return cljs.core.compare_indexed.call(null,x,y);
});

/**
* @constructor
*/
cljs.core.Atom = (function (state,meta,validator,watches){
this.state = state;
this.meta = meta;
this.validator = validator;
this.watches = watches;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 2690809856;
})
cljs.core.Atom.cljs$lang$type = true;
cljs.core.Atom.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/Atom");
});
cljs.core.Atom.prototype.cljs$core$IHash$_hash$arity$1 = (function (this$){
var this__9938 = this;
return goog.getUid(this$);
});
cljs.core.Atom.prototype.cljs$core$IWatchable$_notify_watches$arity$3 = (function (this$,oldval,newval){
var this__9939 = this;
var G__9940__9941 = cljs.core.seq.call(null,this__9939.watches);
if(G__9940__9941)
{var G__9943__9945 = cljs.core.first.call(null,G__9940__9941);
var vec__9944__9946 = G__9943__9945;
var key__9947 = cljs.core.nth.call(null,vec__9944__9946,0,null);
var f__9948 = cljs.core.nth.call(null,vec__9944__9946,1,null);
var G__9940__9949 = G__9940__9941;
var G__9943__9950 = G__9943__9945;
var G__9940__9951 = G__9940__9949;
while(true){
var vec__9952__9953 = G__9943__9950;
var key__9954 = cljs.core.nth.call(null,vec__9952__9953,0,null);
var f__9955 = cljs.core.nth.call(null,vec__9952__9953,1,null);
var G__9940__9956 = G__9940__9951;
f__9955.call(null,key__9954,this$,oldval,newval);
var temp__3974__auto____9957 = cljs.core.next.call(null,G__9940__9956);
if(temp__3974__auto____9957)
{var G__9940__9958 = temp__3974__auto____9957;
{
var G__9965 = cljs.core.first.call(null,G__9940__9958);
var G__9966 = G__9940__9958;
G__9943__9950 = G__9965;
G__9940__9951 = G__9966;
continue;
}
} else
{return null;
}
break;
}
} else
{return null;
}
});
cljs.core.Atom.prototype.cljs$core$IWatchable$_add_watch$arity$3 = (function (this$,key,f){
var this__9959 = this;
return this$.watches = cljs.core.assoc.call(null,this__9959.watches,key,f);
});
cljs.core.Atom.prototype.cljs$core$IWatchable$_remove_watch$arity$2 = (function (this$,key){
var this__9960 = this;
return this$.watches = cljs.core.dissoc.call(null,this__9960.watches,key);
});
cljs.core.Atom.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (a,opts){
var this__9961 = this;
return cljs.core.concat.call(null,cljs.core.PersistentVector.fromArray(["#<Atom: "], true),cljs.core._pr_seq.call(null,this__9961.state,opts),">");
});
cljs.core.Atom.prototype.cljs$core$IMeta$_meta$arity$1 = (function (_){
var this__9962 = this;
return this__9962.meta;
});
cljs.core.Atom.prototype.cljs$core$IDeref$_deref$arity$1 = (function (_){
var this__9963 = this;
return this__9963.state;
});
cljs.core.Atom.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (o,other){
var this__9964 = this;
return (o === other);
});
cljs.core.Atom;
/**
* Creates and returns an Atom with an initial value of x and zero or
* more options (in any order):
* 
* :meta metadata-map
* 
* :validator validate-fn
* 
* If metadata-map is supplied, it will be come the metadata on the
* atom. validate-fn must be nil or a side-effect-free fn of one
* argument, which will be passed the intended new state on any state
* change. If the new state is unacceptable, the validate-fn should
* return false or throw an Error.  If either of these error conditions
* occur, then the value of the atom will not change.
* @param {...*} var_args
*/
cljs.core.atom = (function() {
var atom = null;
var atom__1 = (function (x){
return (new cljs.core.Atom(x,null,null,null));
});
var atom__2 = (function() { 
var G__9978__delegate = function (x,p__9967){
var map__9973__9974 = p__9967;
var map__9973__9975 = ((cljs.core.seq_QMARK_.call(null,map__9973__9974))?cljs.core.apply.call(null,cljs.core.hash_map,map__9973__9974):map__9973__9974);
var validator__9976 = cljs.core._lookup.call(null,map__9973__9975,"\uFDD0'validator",null);
var meta__9977 = cljs.core._lookup.call(null,map__9973__9975,"\uFDD0'meta",null);
return (new cljs.core.Atom(x,meta__9977,validator__9976,null));
};
var G__9978 = function (x,var_args){
var p__9967 = null;
if (goog.isDef(var_args)) {
  p__9967 = cljs.core.array_seq(Array.prototype.slice.call(arguments, 1),0);
} 
return G__9978__delegate.call(this, x, p__9967);
};
G__9978.cljs$lang$maxFixedArity = 1;
G__9978.cljs$lang$applyTo = (function (arglist__9979){
var x = cljs.core.first(arglist__9979);
var p__9967 = cljs.core.rest(arglist__9979);
return G__9978__delegate(x, p__9967);
});
G__9978.cljs$lang$arity$variadic = G__9978__delegate;
return G__9978;
})()
;
atom = function(x,var_args){
var p__9967 = var_args;
switch(arguments.length){
case 1:
return atom__1.call(this,x);
default:
return atom__2.cljs$lang$arity$variadic(x, cljs.core.array_seq(arguments, 1));
}
throw('Invalid arity: ' + arguments.length);
};
atom.cljs$lang$maxFixedArity = 1;
atom.cljs$lang$applyTo = atom__2.cljs$lang$applyTo;
atom.cljs$lang$arity$1 = atom__1;
atom.cljs$lang$arity$variadic = atom__2.cljs$lang$arity$variadic;
return atom;
})()
;
/**
* Sets the value of atom to newval without regard for the
* current value. Returns newval.
*/
cljs.core.reset_BANG_ = (function reset_BANG_(a,new_value){
var temp__3974__auto____9983 = a.validator;
if(cljs.core.truth_(temp__3974__auto____9983))
{var validate__9984 = temp__3974__auto____9983;
if(cljs.core.truth_(validate__9984.call(null,new_value)))
{} else
{throw (new Error([cljs.core.str("Assert failed: "),cljs.core.str("Validator rejected reference state"),cljs.core.str("\n"),cljs.core.str(cljs.core.pr_str.call(null,cljs.core.with_meta(cljs.core.list("\uFDD1'validate","\uFDD1'new-value"),cljs.core.hash_map("\uFDD0'line",6440))))].join('')));
}
} else
{}
var old_value__9985 = a.state;
a.state = new_value;
cljs.core._notify_watches.call(null,a,old_value__9985,new_value);
return new_value;
});
/**
* Atomically swaps the value of atom to be:
* (apply f current-value-of-atom args). Note that f may be called
* multiple times, and thus should be free of side effects.  Returns
* the value that was swapped in.
* @param {...*} var_args
*/
cljs.core.swap_BANG_ = (function() {
var swap_BANG_ = null;
var swap_BANG___2 = (function (a,f){
return cljs.core.reset_BANG_.call(null,a,f.call(null,a.state));
});
var swap_BANG___3 = (function (a,f,x){
return cljs.core.reset_BANG_.call(null,a,f.call(null,a.state,x));
});
var swap_BANG___4 = (function (a,f,x,y){
return cljs.core.reset_BANG_.call(null,a,f.call(null,a.state,x,y));
});
var swap_BANG___5 = (function (a,f,x,y,z){
return cljs.core.reset_BANG_.call(null,a,f.call(null,a.state,x,y,z));
});
var swap_BANG___6 = (function() { 
var G__9986__delegate = function (a,f,x,y,z,more){
return cljs.core.reset_BANG_.call(null,a,cljs.core.apply.call(null,f,a.state,x,y,z,more));
};
var G__9986 = function (a,f,x,y,z,var_args){
var more = null;
if (goog.isDef(var_args)) {
  more = cljs.core.array_seq(Array.prototype.slice.call(arguments, 5),0);
} 
return G__9986__delegate.call(this, a, f, x, y, z, more);
};
G__9986.cljs$lang$maxFixedArity = 5;
G__9986.cljs$lang$applyTo = (function (arglist__9987){
var a = cljs.core.first(arglist__9987);
var f = cljs.core.first(cljs.core.next(arglist__9987));
var x = cljs.core.first(cljs.core.next(cljs.core.next(arglist__9987)));
var y = cljs.core.first(cljs.core.next(cljs.core.next(cljs.core.next(arglist__9987))));
var z = cljs.core.first(cljs.core.next(cljs.core.next(cljs.core.next(cljs.core.next(arglist__9987)))));
var more = cljs.core.rest(cljs.core.next(cljs.core.next(cljs.core.next(cljs.core.next(arglist__9987)))));
return G__9986__delegate(a, f, x, y, z, more);
});
G__9986.cljs$lang$arity$variadic = G__9986__delegate;
return G__9986;
})()
;
swap_BANG_ = function(a,f,x,y,z,var_args){
var more = var_args;
switch(arguments.length){
case 2:
return swap_BANG___2.call(this,a,f);
case 3:
return swap_BANG___3.call(this,a,f,x);
case 4:
return swap_BANG___4.call(this,a,f,x,y);
case 5:
return swap_BANG___5.call(this,a,f,x,y,z);
default:
return swap_BANG___6.cljs$lang$arity$variadic(a,f,x,y,z, cljs.core.array_seq(arguments, 5));
}
throw('Invalid arity: ' + arguments.length);
};
swap_BANG_.cljs$lang$maxFixedArity = 5;
swap_BANG_.cljs$lang$applyTo = swap_BANG___6.cljs$lang$applyTo;
swap_BANG_.cljs$lang$arity$2 = swap_BANG___2;
swap_BANG_.cljs$lang$arity$3 = swap_BANG___3;
swap_BANG_.cljs$lang$arity$4 = swap_BANG___4;
swap_BANG_.cljs$lang$arity$5 = swap_BANG___5;
swap_BANG_.cljs$lang$arity$variadic = swap_BANG___6.cljs$lang$arity$variadic;
return swap_BANG_;
})()
;
/**
* Atomically sets the value of atom to newval if and only if the
* current value of the atom is identical to oldval. Returns true if
* set happened, else false.
*/
cljs.core.compare_and_set_BANG_ = (function compare_and_set_BANG_(a,oldval,newval){
if(cljs.core._EQ_.call(null,a.state,oldval))
{cljs.core.reset_BANG_.call(null,a,newval);
return true;
} else
{return false;
}
});
cljs.core.deref = (function deref(o){
return cljs.core._deref.call(null,o);
});
/**
* Sets the validator-fn for an atom. validator-fn must be nil or a
* side-effect-free fn of one argument, which will be passed the intended
* new state on any state change. If the new state is unacceptable, the
* validator-fn should return false or throw an Error. If the current state
* is not acceptable to the new validator, an Error will be thrown and the
* validator will not be changed.
*/
cljs.core.set_validator_BANG_ = (function set_validator_BANG_(iref,val){
return iref.validator = val;
});
/**
* Gets the validator-fn for a var/ref/agent/atom.
*/
cljs.core.get_validator = (function get_validator(iref){
return iref.validator;
});
/**
* Atomically sets the metadata for a namespace/var/ref/agent/atom to be:
* 
* (apply f its-current-meta args)
* 
* f must be free of side-effects
* @param {...*} var_args
*/
cljs.core.alter_meta_BANG_ = (function() { 
var alter_meta_BANG___delegate = function (iref,f,args){
return iref.meta = cljs.core.apply.call(null,f,iref.meta,args);
};
var alter_meta_BANG_ = function (iref,f,var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 2),0);
} 
return alter_meta_BANG___delegate.call(this, iref, f, args);
};
alter_meta_BANG_.cljs$lang$maxFixedArity = 2;
alter_meta_BANG_.cljs$lang$applyTo = (function (arglist__9988){
var iref = cljs.core.first(arglist__9988);
var f = cljs.core.first(cljs.core.next(arglist__9988));
var args = cljs.core.rest(cljs.core.next(arglist__9988));
return alter_meta_BANG___delegate(iref, f, args);
});
alter_meta_BANG_.cljs$lang$arity$variadic = alter_meta_BANG___delegate;
return alter_meta_BANG_;
})()
;
/**
* Atomically resets the metadata for an atom
*/
cljs.core.reset_meta_BANG_ = (function reset_meta_BANG_(iref,m){
return iref.meta = m;
});
/**
* Alpha - subject to change.
* 
* Adds a watch function to an atom reference. The watch fn must be a
* fn of 4 args: a key, the reference, its old-state, its
* new-state. Whenever the reference's state might have been changed,
* any registered watches will have their functions called. The watch
* fn will be called synchronously. Note that an atom's state
* may have changed again prior to the fn call, so use old/new-state
* rather than derefing the reference. Keys must be unique per
* reference, and can be used to remove the watch with remove-watch,
* but are otherwise considered opaque by the watch mechanism.  Bear in
* mind that regardless of the result or action of the watch fns the
* atom's value will change.  Example:
* 
* (def a (atom 0))
* (add-watch a :inc (fn [k r o n] (assert (== 0 n))))
* (swap! a inc)
* ;; Assertion Error
* (deref a)
* ;=> 1
*/
cljs.core.add_watch = (function add_watch(iref,key,f){
return cljs.core._add_watch.call(null,iref,key,f);
});
/**
* Alpha - subject to change.
* 
* Removes a watch (set by add-watch) from a reference
*/
cljs.core.remove_watch = (function remove_watch(iref,key){
return cljs.core._remove_watch.call(null,iref,key);
});
cljs.core.gensym_counter = null;
/**
* Returns a new symbol with a unique name. If a prefix string is
* supplied, the name is prefix# where # is some unique number. If
* prefix is not supplied, the prefix is 'G__'.
*/
cljs.core.gensym = (function() {
var gensym = null;
var gensym__0 = (function (){
return gensym.call(null,"G__");
});
var gensym__1 = (function (prefix_string){
if((cljs.core.gensym_counter == null))
{cljs.core.gensym_counter = cljs.core.atom.call(null,0);
} else
{}
return cljs.core.symbol.call(null,[cljs.core.str(prefix_string),cljs.core.str(cljs.core.swap_BANG_.call(null,cljs.core.gensym_counter,cljs.core.inc))].join(''));
});
gensym = function(prefix_string){
switch(arguments.length){
case 0:
return gensym__0.call(this);
case 1:
return gensym__1.call(this,prefix_string);
}
throw('Invalid arity: ' + arguments.length);
};
gensym.cljs$lang$arity$0 = gensym__0;
gensym.cljs$lang$arity$1 = gensym__1;
return gensym;
})()
;
cljs.core.fixture1 = 1;
cljs.core.fixture2 = 2;

/**
* @constructor
*/
cljs.core.Delay = (function (state,f){
this.state = state;
this.f = f;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 1073774592;
})
cljs.core.Delay.cljs$lang$type = true;
cljs.core.Delay.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/Delay");
});
cljs.core.Delay.prototype.cljs$core$IPending$_realized_QMARK_$arity$1 = (function (d){
var this__9989 = this;
return (new cljs.core.Keyword("\uFDD0'done")).call(null,cljs.core.deref.call(null,this__9989.state));
});
cljs.core.Delay.prototype.cljs$core$IDeref$_deref$arity$1 = (function (_){
var this__9990 = this;
return (new cljs.core.Keyword("\uFDD0'value")).call(null,cljs.core.swap_BANG_.call(null,this__9990.state,(function (p__9991){
var map__9992__9993 = p__9991;
var map__9992__9994 = ((cljs.core.seq_QMARK_.call(null,map__9992__9993))?cljs.core.apply.call(null,cljs.core.hash_map,map__9992__9993):map__9992__9993);
var curr_state__9995 = map__9992__9994;
var done__9996 = cljs.core._lookup.call(null,map__9992__9994,"\uFDD0'done",null);
if(cljs.core.truth_(done__9996))
{return curr_state__9995;
} else
{return cljs.core.ObjMap.fromObject(["\uFDD0'done","\uFDD0'value"],{"\uFDD0'done":true,"\uFDD0'value":this__9990.f.call(null)});
}
})));
});
cljs.core.Delay;
/**
* returns true if x is a Delay created with delay
*/
cljs.core.delay_QMARK_ = (function delay_QMARK_(x){
return cljs.core.instance_QMARK_.call(null,cljs.core.Delay,x);
});
/**
* If x is a Delay, returns the (possibly cached) value of its expression, else returns x
*/
cljs.core.force = (function force(x){
if(cljs.core.delay_QMARK_.call(null,x))
{return cljs.core.deref.call(null,x);
} else
{return x;
}
});
/**
* Returns true if a value has been produced for a promise, delay, future or lazy sequence.
*/
cljs.core.realized_QMARK_ = (function realized_QMARK_(d){
return cljs.core._realized_QMARK_.call(null,d);
});
/**
* Recursively transforms JavaScript arrays into ClojureScript
* vectors, and JavaScript objects into ClojureScript maps.  With
* option ':keywordize-keys true' will convert object fields from
* strings to keywords.
* @param {...*} var_args
*/
cljs.core.js__GT_clj = (function() { 
var js__GT_clj__delegate = function (x,options){
var map__10017__10018 = options;
var map__10017__10019 = ((cljs.core.seq_QMARK_.call(null,map__10017__10018))?cljs.core.apply.call(null,cljs.core.hash_map,map__10017__10018):map__10017__10018);
var keywordize_keys__10020 = cljs.core._lookup.call(null,map__10017__10019,"\uFDD0'keywordize-keys",null);
var keyfn__10021 = (cljs.core.truth_(keywordize_keys__10020)?cljs.core.keyword:cljs.core.str);
var f__10036 = (function thisfn(x){
if(cljs.core.seq_QMARK_.call(null,x))
{return cljs.core.doall.call(null,cljs.core.map.call(null,thisfn,x));
} else
{if(cljs.core.coll_QMARK_.call(null,x))
{return cljs.core.into.call(null,cljs.core.empty.call(null,x),cljs.core.map.call(null,thisfn,x));
} else
{if(cljs.core.truth_(goog.isArray(x)))
{return cljs.core.vec.call(null,cljs.core.map.call(null,thisfn,x));
} else
{if((cljs.core.type.call(null,x) === Object))
{return cljs.core.into.call(null,cljs.core.ObjMap.EMPTY,(function (){var iter__2490__auto____10035 = (function iter__10029(s__10030){
return (new cljs.core.LazySeq(null,false,(function (){
var s__10030__10033 = s__10030;
while(true){
if(cljs.core.seq.call(null,s__10030__10033))
{var k__10034 = cljs.core.first.call(null,s__10030__10033);
return cljs.core.cons.call(null,cljs.core.PersistentVector.fromArray([keyfn__10021.call(null,k__10034),thisfn.call(null,(x[k__10034]))], true),iter__10029.call(null,cljs.core.rest.call(null,s__10030__10033)));
} else
{return null;
}
break;
}
}),null));
});
return iter__2490__auto____10035.call(null,cljs.core.js_keys.call(null,x));
})());
} else
{if("\uFDD0'else")
{return x;
} else
{return null;
}
}
}
}
}
});
return f__10036.call(null,x);
};
var js__GT_clj = function (x,var_args){
var options = null;
if (goog.isDef(var_args)) {
  options = cljs.core.array_seq(Array.prototype.slice.call(arguments, 1),0);
} 
return js__GT_clj__delegate.call(this, x, options);
};
js__GT_clj.cljs$lang$maxFixedArity = 1;
js__GT_clj.cljs$lang$applyTo = (function (arglist__10037){
var x = cljs.core.first(arglist__10037);
var options = cljs.core.rest(arglist__10037);
return js__GT_clj__delegate(x, options);
});
js__GT_clj.cljs$lang$arity$variadic = js__GT_clj__delegate;
return js__GT_clj;
})()
;
/**
* Returns a memoized version of a referentially transparent function. The
* memoized version of the function keeps a cache of the mapping from arguments
* to results and, when calls with the same arguments are repeated often, has
* higher performance at the expense of higher memory use.
*/
cljs.core.memoize = (function memoize(f){
var mem__10042 = cljs.core.atom.call(null,cljs.core.ObjMap.EMPTY);
return (function() { 
var G__10046__delegate = function (args){
var temp__3971__auto____10043 = cljs.core._lookup.call(null,cljs.core.deref.call(null,mem__10042),args,null);
if(cljs.core.truth_(temp__3971__auto____10043))
{var v__10044 = temp__3971__auto____10043;
return v__10044;
} else
{var ret__10045 = cljs.core.apply.call(null,f,args);
cljs.core.swap_BANG_.call(null,mem__10042,cljs.core.assoc,args,ret__10045);
return ret__10045;
}
};
var G__10046 = function (var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 0),0);
} 
return G__10046__delegate.call(this, args);
};
G__10046.cljs$lang$maxFixedArity = 0;
G__10046.cljs$lang$applyTo = (function (arglist__10047){
var args = cljs.core.seq(arglist__10047);;
return G__10046__delegate(args);
});
G__10046.cljs$lang$arity$variadic = G__10046__delegate;
return G__10046;
})()
;
});
/**
* trampoline can be used to convert algorithms requiring mutual
* recursion without stack consumption. Calls f with supplied args, if
* any. If f returns a fn, calls that fn with no arguments, and
* continues to repeat, until the return value is not a fn, then
* returns that non-fn value. Note that if you want to return a fn as a
* final value, you must wrap it in some data structure and unpack it
* after trampoline returns.
* @param {...*} var_args
*/
cljs.core.trampoline = (function() {
var trampoline = null;
var trampoline__1 = (function (f){
while(true){
var ret__10049 = f.call(null);
if(cljs.core.fn_QMARK_.call(null,ret__10049))
{{
var G__10050 = ret__10049;
f = G__10050;
continue;
}
} else
{return ret__10049;
}
break;
}
});
var trampoline__2 = (function() { 
var G__10051__delegate = function (f,args){
return trampoline.call(null,(function (){
return cljs.core.apply.call(null,f,args);
}));
};
var G__10051 = function (f,var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 1),0);
} 
return G__10051__delegate.call(this, f, args);
};
G__10051.cljs$lang$maxFixedArity = 1;
G__10051.cljs$lang$applyTo = (function (arglist__10052){
var f = cljs.core.first(arglist__10052);
var args = cljs.core.rest(arglist__10052);
return G__10051__delegate(f, args);
});
G__10051.cljs$lang$arity$variadic = G__10051__delegate;
return G__10051;
})()
;
trampoline = function(f,var_args){
var args = var_args;
switch(arguments.length){
case 1:
return trampoline__1.call(this,f);
default:
return trampoline__2.cljs$lang$arity$variadic(f, cljs.core.array_seq(arguments, 1));
}
throw('Invalid arity: ' + arguments.length);
};
trampoline.cljs$lang$maxFixedArity = 1;
trampoline.cljs$lang$applyTo = trampoline__2.cljs$lang$applyTo;
trampoline.cljs$lang$arity$1 = trampoline__1;
trampoline.cljs$lang$arity$variadic = trampoline__2.cljs$lang$arity$variadic;
return trampoline;
})()
;
/**
* Returns a random floating point number between 0 (inclusive) and
* n (default 1) (exclusive).
*/
cljs.core.rand = (function() {
var rand = null;
var rand__0 = (function (){
return rand.call(null,1);
});
var rand__1 = (function (n){
return (Math.random.call(null) * n);
});
rand = function(n){
switch(arguments.length){
case 0:
return rand__0.call(this);
case 1:
return rand__1.call(this,n);
}
throw('Invalid arity: ' + arguments.length);
};
rand.cljs$lang$arity$0 = rand__0;
rand.cljs$lang$arity$1 = rand__1;
return rand;
})()
;
/**
* Returns a random integer between 0 (inclusive) and n (exclusive).
*/
cljs.core.rand_int = (function rand_int(n){
return Math.floor.call(null,(Math.random.call(null) * n));
});
/**
* Return a random element of the (sequential) collection. Will have
* the same performance characteristics as nth for the given
* collection.
*/
cljs.core.rand_nth = (function rand_nth(coll){
return cljs.core.nth.call(null,coll,cljs.core.rand_int.call(null,cljs.core.count.call(null,coll)));
});
/**
* Returns a map of the elements of coll keyed by the result of
* f on each element. The value at each key will be a vector of the
* corresponding elements, in the order they appeared in coll.
*/
cljs.core.group_by = (function group_by(f,coll){
return cljs.core.reduce.call(null,(function (ret,x){
var k__10054 = f.call(null,x);
return cljs.core.assoc.call(null,ret,k__10054,cljs.core.conj.call(null,cljs.core._lookup.call(null,ret,k__10054,cljs.core.PersistentVector.EMPTY),x));
}),cljs.core.ObjMap.EMPTY,coll);
});
/**
* Creates a hierarchy object for use with derive, isa? etc.
*/
cljs.core.make_hierarchy = (function make_hierarchy(){
return cljs.core.ObjMap.fromObject(["\uFDD0'parents","\uFDD0'descendants","\uFDD0'ancestors"],{"\uFDD0'parents":cljs.core.ObjMap.EMPTY,"\uFDD0'descendants":cljs.core.ObjMap.EMPTY,"\uFDD0'ancestors":cljs.core.ObjMap.EMPTY});
});
cljs.core.global_hierarchy = cljs.core.atom.call(null,cljs.core.make_hierarchy.call(null));
/**
* Returns true if (= child parent), or child is directly or indirectly derived from
* parent, either via a JavaScript type inheritance relationship or a
* relationship established via derive. h must be a hierarchy obtained
* from make-hierarchy, if not supplied defaults to the global
* hierarchy
*/
cljs.core.isa_QMARK_ = (function() {
var isa_QMARK_ = null;
var isa_QMARK___2 = (function (child,parent){
return isa_QMARK_.call(null,cljs.core.deref.call(null,cljs.core.global_hierarchy),child,parent);
});
var isa_QMARK___3 = (function (h,child,parent){
var or__3824__auto____10063 = cljs.core._EQ_.call(null,child,parent);
if(or__3824__auto____10063)
{return or__3824__auto____10063;
} else
{var or__3824__auto____10064 = cljs.core.contains_QMARK_.call(null,(new cljs.core.Keyword("\uFDD0'ancestors")).call(null,h).call(null,child),parent);
if(or__3824__auto____10064)
{return or__3824__auto____10064;
} else
{var and__3822__auto____10065 = cljs.core.vector_QMARK_.call(null,parent);
if(and__3822__auto____10065)
{var and__3822__auto____10066 = cljs.core.vector_QMARK_.call(null,child);
if(and__3822__auto____10066)
{var and__3822__auto____10067 = (cljs.core.count.call(null,parent) === cljs.core.count.call(null,child));
if(and__3822__auto____10067)
{var ret__10068 = true;
var i__10069 = 0;
while(true){
if((function (){var or__3824__auto____10070 = cljs.core.not.call(null,ret__10068);
if(or__3824__auto____10070)
{return or__3824__auto____10070;
} else
{return (i__10069 === cljs.core.count.call(null,parent));
}
})())
{return ret__10068;
} else
{{
var G__10071 = isa_QMARK_.call(null,h,child.call(null,i__10069),parent.call(null,i__10069));
var G__10072 = (i__10069 + 1);
ret__10068 = G__10071;
i__10069 = G__10072;
continue;
}
}
break;
}
} else
{return and__3822__auto____10067;
}
} else
{return and__3822__auto____10066;
}
} else
{return and__3822__auto____10065;
}
}
}
});
isa_QMARK_ = function(h,child,parent){
switch(arguments.length){
case 2:
return isa_QMARK___2.call(this,h,child);
case 3:
return isa_QMARK___3.call(this,h,child,parent);
}
throw('Invalid arity: ' + arguments.length);
};
isa_QMARK_.cljs$lang$arity$2 = isa_QMARK___2;
isa_QMARK_.cljs$lang$arity$3 = isa_QMARK___3;
return isa_QMARK_;
})()
;
/**
* Returns the immediate parents of tag, either via a JavaScript type
* inheritance relationship or a relationship established via derive. h
* must be a hierarchy obtained from make-hierarchy, if not supplied
* defaults to the global hierarchy
*/
cljs.core.parents = (function() {
var parents = null;
var parents__1 = (function (tag){
return parents.call(null,cljs.core.deref.call(null,cljs.core.global_hierarchy),tag);
});
var parents__2 = (function (h,tag){
return cljs.core.not_empty.call(null,cljs.core._lookup.call(null,(new cljs.core.Keyword("\uFDD0'parents")).call(null,h),tag,null));
});
parents = function(h,tag){
switch(arguments.length){
case 1:
return parents__1.call(this,h);
case 2:
return parents__2.call(this,h,tag);
}
throw('Invalid arity: ' + arguments.length);
};
parents.cljs$lang$arity$1 = parents__1;
parents.cljs$lang$arity$2 = parents__2;
return parents;
})()
;
/**
* Returns the immediate and indirect parents of tag, either via a JavaScript type
* inheritance relationship or a relationship established via derive. h
* must be a hierarchy obtained from make-hierarchy, if not supplied
* defaults to the global hierarchy
*/
cljs.core.ancestors = (function() {
var ancestors = null;
var ancestors__1 = (function (tag){
return ancestors.call(null,cljs.core.deref.call(null,cljs.core.global_hierarchy),tag);
});
var ancestors__2 = (function (h,tag){
return cljs.core.not_empty.call(null,cljs.core._lookup.call(null,(new cljs.core.Keyword("\uFDD0'ancestors")).call(null,h),tag,null));
});
ancestors = function(h,tag){
switch(arguments.length){
case 1:
return ancestors__1.call(this,h);
case 2:
return ancestors__2.call(this,h,tag);
}
throw('Invalid arity: ' + arguments.length);
};
ancestors.cljs$lang$arity$1 = ancestors__1;
ancestors.cljs$lang$arity$2 = ancestors__2;
return ancestors;
})()
;
/**
* Returns the immediate and indirect children of tag, through a
* relationship established via derive. h must be a hierarchy obtained
* from make-hierarchy, if not supplied defaults to the global
* hierarchy. Note: does not work on JavaScript type inheritance
* relationships.
*/
cljs.core.descendants = (function() {
var descendants = null;
var descendants__1 = (function (tag){
return descendants.call(null,cljs.core.deref.call(null,cljs.core.global_hierarchy),tag);
});
var descendants__2 = (function (h,tag){
return cljs.core.not_empty.call(null,cljs.core._lookup.call(null,(new cljs.core.Keyword("\uFDD0'descendants")).call(null,h),tag,null));
});
descendants = function(h,tag){
switch(arguments.length){
case 1:
return descendants__1.call(this,h);
case 2:
return descendants__2.call(this,h,tag);
}
throw('Invalid arity: ' + arguments.length);
};
descendants.cljs$lang$arity$1 = descendants__1;
descendants.cljs$lang$arity$2 = descendants__2;
return descendants;
})()
;
/**
* Establishes a parent/child relationship between parent and
* tag. Parent must be a namespace-qualified symbol or keyword and
* child can be either a namespace-qualified symbol or keyword or a
* class. h must be a hierarchy obtained from make-hierarchy, if not
* supplied defaults to, and modifies, the global hierarchy.
*/
cljs.core.derive = (function() {
var derive = null;
var derive__2 = (function (tag,parent){
if(cljs.core.truth_(cljs.core.namespace.call(null,parent)))
{} else
{throw (new Error([cljs.core.str("Assert failed: "),cljs.core.str(cljs.core.pr_str.call(null,cljs.core.with_meta(cljs.core.list("\uFDD1'namespace","\uFDD1'parent"),cljs.core.hash_map("\uFDD0'line",6724))))].join('')));
}
cljs.core.swap_BANG_.call(null,cljs.core.global_hierarchy,derive,tag,parent);
return null;
});
var derive__3 = (function (h,tag,parent){
if(cljs.core.not_EQ_.call(null,tag,parent))
{} else
{throw (new Error([cljs.core.str("Assert failed: "),cljs.core.str(cljs.core.pr_str.call(null,cljs.core.with_meta(cljs.core.list("\uFDD1'not=","\uFDD1'tag","\uFDD1'parent"),cljs.core.hash_map("\uFDD0'line",6728))))].join('')));
}
var tp__10081 = (new cljs.core.Keyword("\uFDD0'parents")).call(null,h);
var td__10082 = (new cljs.core.Keyword("\uFDD0'descendants")).call(null,h);
var ta__10083 = (new cljs.core.Keyword("\uFDD0'ancestors")).call(null,h);
var tf__10084 = (function (m,source,sources,target,targets){
return cljs.core.reduce.call(null,(function (ret,k){
return cljs.core.assoc.call(null,ret,k,cljs.core.reduce.call(null,cljs.core.conj,cljs.core._lookup.call(null,targets,k,cljs.core.PersistentHashSet.EMPTY),cljs.core.cons.call(null,target,targets.call(null,target))));
}),m,cljs.core.cons.call(null,source,sources.call(null,source)));
});
var or__3824__auto____10085 = ((cljs.core.contains_QMARK_.call(null,tp__10081.call(null,tag),parent))?null:(function (){if(cljs.core.contains_QMARK_.call(null,ta__10083.call(null,tag),parent))
{throw (new Error([cljs.core.str(tag),cljs.core.str("already has"),cljs.core.str(parent),cljs.core.str("as ancestor")].join('')));
} else
{}
if(cljs.core.contains_QMARK_.call(null,ta__10083.call(null,parent),tag))
{throw (new Error([cljs.core.str("Cyclic derivation:"),cljs.core.str(parent),cljs.core.str("has"),cljs.core.str(tag),cljs.core.str("as ancestor")].join('')));
} else
{}
return cljs.core.ObjMap.fromObject(["\uFDD0'parents","\uFDD0'ancestors","\uFDD0'descendants"],{"\uFDD0'parents":cljs.core.assoc.call(null,(new cljs.core.Keyword("\uFDD0'parents")).call(null,h),tag,cljs.core.conj.call(null,cljs.core._lookup.call(null,tp__10081,tag,cljs.core.PersistentHashSet.EMPTY),parent)),"\uFDD0'ancestors":tf__10084.call(null,(new cljs.core.Keyword("\uFDD0'ancestors")).call(null,h),tag,td__10082,parent,ta__10083),"\uFDD0'descendants":tf__10084.call(null,(new cljs.core.Keyword("\uFDD0'descendants")).call(null,h),parent,ta__10083,tag,td__10082)});
})());
if(cljs.core.truth_(or__3824__auto____10085))
{return or__3824__auto____10085;
} else
{return h;
}
});
derive = function(h,tag,parent){
switch(arguments.length){
case 2:
return derive__2.call(this,h,tag);
case 3:
return derive__3.call(this,h,tag,parent);
}
throw('Invalid arity: ' + arguments.length);
};
derive.cljs$lang$arity$2 = derive__2;
derive.cljs$lang$arity$3 = derive__3;
return derive;
})()
;
/**
* Removes a parent/child relationship between parent and
* tag. h must be a hierarchy obtained from make-hierarchy, if not
* supplied defaults to, and modifies, the global hierarchy.
*/
cljs.core.underive = (function() {
var underive = null;
var underive__2 = (function (tag,parent){
cljs.core.swap_BANG_.call(null,cljs.core.global_hierarchy,underive,tag,parent);
return null;
});
var underive__3 = (function (h,tag,parent){
var parentMap__10090 = (new cljs.core.Keyword("\uFDD0'parents")).call(null,h);
var childsParents__10091 = (cljs.core.truth_(parentMap__10090.call(null,tag))?cljs.core.disj.call(null,parentMap__10090.call(null,tag),parent):cljs.core.PersistentHashSet.EMPTY);
var newParents__10092 = (cljs.core.truth_(cljs.core.not_empty.call(null,childsParents__10091))?cljs.core.assoc.call(null,parentMap__10090,tag,childsParents__10091):cljs.core.dissoc.call(null,parentMap__10090,tag));
var deriv_seq__10093 = cljs.core.flatten.call(null,cljs.core.map.call(null,(function (p1__10073_SHARP_){
return cljs.core.cons.call(null,cljs.core.first.call(null,p1__10073_SHARP_),cljs.core.interpose.call(null,cljs.core.first.call(null,p1__10073_SHARP_),cljs.core.second.call(null,p1__10073_SHARP_)));
}),cljs.core.seq.call(null,newParents__10092)));
if(cljs.core.contains_QMARK_.call(null,parentMap__10090.call(null,tag),parent))
{return cljs.core.reduce.call(null,(function (p1__10074_SHARP_,p2__10075_SHARP_){
return cljs.core.apply.call(null,cljs.core.derive,p1__10074_SHARP_,p2__10075_SHARP_);
}),cljs.core.make_hierarchy.call(null),cljs.core.partition.call(null,2,deriv_seq__10093));
} else
{return h;
}
});
underive = function(h,tag,parent){
switch(arguments.length){
case 2:
return underive__2.call(this,h,tag);
case 3:
return underive__3.call(this,h,tag,parent);
}
throw('Invalid arity: ' + arguments.length);
};
underive.cljs$lang$arity$2 = underive__2;
underive.cljs$lang$arity$3 = underive__3;
return underive;
})()
;
cljs.core.reset_cache = (function reset_cache(method_cache,method_table,cached_hierarchy,hierarchy){
cljs.core.swap_BANG_.call(null,method_cache,(function (_){
return cljs.core.deref.call(null,method_table);
}));
return cljs.core.swap_BANG_.call(null,cached_hierarchy,(function (_){
return cljs.core.deref.call(null,hierarchy);
}));
});
cljs.core.prefers_STAR_ = (function prefers_STAR_(x,y,prefer_table){
var xprefs__10101 = cljs.core.deref.call(null,prefer_table).call(null,x);
var or__3824__auto____10103 = (cljs.core.truth_((function (){var and__3822__auto____10102 = xprefs__10101;
if(cljs.core.truth_(and__3822__auto____10102))
{return xprefs__10101.call(null,y);
} else
{return and__3822__auto____10102;
}
})())?true:null);
if(cljs.core.truth_(or__3824__auto____10103))
{return or__3824__auto____10103;
} else
{var or__3824__auto____10105 = (function (){var ps__10104 = cljs.core.parents.call(null,y);
while(true){
if((cljs.core.count.call(null,ps__10104) > 0))
{if(cljs.core.truth_(prefers_STAR_.call(null,x,cljs.core.first.call(null,ps__10104),prefer_table)))
{} else
{}
{
var G__10108 = cljs.core.rest.call(null,ps__10104);
ps__10104 = G__10108;
continue;
}
} else
{return null;
}
break;
}
})();
if(cljs.core.truth_(or__3824__auto____10105))
{return or__3824__auto____10105;
} else
{var or__3824__auto____10107 = (function (){var ps__10106 = cljs.core.parents.call(null,x);
while(true){
if((cljs.core.count.call(null,ps__10106) > 0))
{if(cljs.core.truth_(prefers_STAR_.call(null,cljs.core.first.call(null,ps__10106),y,prefer_table)))
{} else
{}
{
var G__10109 = cljs.core.rest.call(null,ps__10106);
ps__10106 = G__10109;
continue;
}
} else
{return null;
}
break;
}
})();
if(cljs.core.truth_(or__3824__auto____10107))
{return or__3824__auto____10107;
} else
{return false;
}
}
}
});
cljs.core.dominates = (function dominates(x,y,prefer_table){
var or__3824__auto____10111 = cljs.core.prefers_STAR_.call(null,x,y,prefer_table);
if(cljs.core.truth_(or__3824__auto____10111))
{return or__3824__auto____10111;
} else
{return cljs.core.isa_QMARK_.call(null,x,y);
}
});
cljs.core.find_and_cache_best_method = (function find_and_cache_best_method(name,dispatch_val,hierarchy,method_table,prefer_table,method_cache,cached_hierarchy){
var best_entry__10129 = cljs.core.reduce.call(null,(function (be,p__10121){
var vec__10122__10123 = p__10121;
var k__10124 = cljs.core.nth.call(null,vec__10122__10123,0,null);
var ___10125 = cljs.core.nth.call(null,vec__10122__10123,1,null);
var e__10126 = vec__10122__10123;
if(cljs.core.isa_QMARK_.call(null,dispatch_val,k__10124))
{var be2__10128 = (cljs.core.truth_((function (){var or__3824__auto____10127 = (be == null);
if(or__3824__auto____10127)
{return or__3824__auto____10127;
} else
{return cljs.core.dominates.call(null,k__10124,cljs.core.first.call(null,be),prefer_table);
}
})())?e__10126:be);
if(cljs.core.truth_(cljs.core.dominates.call(null,cljs.core.first.call(null,be2__10128),k__10124,prefer_table)))
{} else
{throw (new Error([cljs.core.str("Multiple methods in multimethod '"),cljs.core.str(name),cljs.core.str("' match dispatch value: "),cljs.core.str(dispatch_val),cljs.core.str(" -> "),cljs.core.str(k__10124),cljs.core.str(" and "),cljs.core.str(cljs.core.first.call(null,be2__10128)),cljs.core.str(", and neither is preferred")].join('')));
}
return be2__10128;
} else
{return be;
}
}),null,cljs.core.deref.call(null,method_table));
if(cljs.core.truth_(best_entry__10129))
{if(cljs.core._EQ_.call(null,cljs.core.deref.call(null,cached_hierarchy),cljs.core.deref.call(null,hierarchy)))
{cljs.core.swap_BANG_.call(null,method_cache,cljs.core.assoc,dispatch_val,cljs.core.second.call(null,best_entry__10129));
return cljs.core.second.call(null,best_entry__10129);
} else
{cljs.core.reset_cache.call(null,method_cache,method_table,cached_hierarchy,hierarchy);
return find_and_cache_best_method.call(null,name,dispatch_val,hierarchy,method_table,prefer_table,method_cache,cached_hierarchy);
}
} else
{return null;
}
});
cljs.core.IMultiFn = {};
cljs.core._reset = (function _reset(mf){
if((function (){var and__3822__auto____10134 = mf;
if(and__3822__auto____10134)
{return mf.cljs$core$IMultiFn$_reset$arity$1;
} else
{return and__3822__auto____10134;
}
})())
{return mf.cljs$core$IMultiFn$_reset$arity$1(mf);
} else
{var x__2391__auto____10135 = (((mf == null))?null:mf);
return (function (){var or__3824__auto____10136 = (cljs.core._reset[goog.typeOf(x__2391__auto____10135)]);
if(or__3824__auto____10136)
{return or__3824__auto____10136;
} else
{var or__3824__auto____10137 = (cljs.core._reset["_"]);
if(or__3824__auto____10137)
{return or__3824__auto____10137;
} else
{throw cljs.core.missing_protocol.call(null,"IMultiFn.-reset",mf);
}
}
})().call(null,mf);
}
});
cljs.core._add_method = (function _add_method(mf,dispatch_val,method){
if((function (){var and__3822__auto____10142 = mf;
if(and__3822__auto____10142)
{return mf.cljs$core$IMultiFn$_add_method$arity$3;
} else
{return and__3822__auto____10142;
}
})())
{return mf.cljs$core$IMultiFn$_add_method$arity$3(mf,dispatch_val,method);
} else
{var x__2391__auto____10143 = (((mf == null))?null:mf);
return (function (){var or__3824__auto____10144 = (cljs.core._add_method[goog.typeOf(x__2391__auto____10143)]);
if(or__3824__auto____10144)
{return or__3824__auto____10144;
} else
{var or__3824__auto____10145 = (cljs.core._add_method["_"]);
if(or__3824__auto____10145)
{return or__3824__auto____10145;
} else
{throw cljs.core.missing_protocol.call(null,"IMultiFn.-add-method",mf);
}
}
})().call(null,mf,dispatch_val,method);
}
});
cljs.core._remove_method = (function _remove_method(mf,dispatch_val){
if((function (){var and__3822__auto____10150 = mf;
if(and__3822__auto____10150)
{return mf.cljs$core$IMultiFn$_remove_method$arity$2;
} else
{return and__3822__auto____10150;
}
})())
{return mf.cljs$core$IMultiFn$_remove_method$arity$2(mf,dispatch_val);
} else
{var x__2391__auto____10151 = (((mf == null))?null:mf);
return (function (){var or__3824__auto____10152 = (cljs.core._remove_method[goog.typeOf(x__2391__auto____10151)]);
if(or__3824__auto____10152)
{return or__3824__auto____10152;
} else
{var or__3824__auto____10153 = (cljs.core._remove_method["_"]);
if(or__3824__auto____10153)
{return or__3824__auto____10153;
} else
{throw cljs.core.missing_protocol.call(null,"IMultiFn.-remove-method",mf);
}
}
})().call(null,mf,dispatch_val);
}
});
cljs.core._prefer_method = (function _prefer_method(mf,dispatch_val,dispatch_val_y){
if((function (){var and__3822__auto____10158 = mf;
if(and__3822__auto____10158)
{return mf.cljs$core$IMultiFn$_prefer_method$arity$3;
} else
{return and__3822__auto____10158;
}
})())
{return mf.cljs$core$IMultiFn$_prefer_method$arity$3(mf,dispatch_val,dispatch_val_y);
} else
{var x__2391__auto____10159 = (((mf == null))?null:mf);
return (function (){var or__3824__auto____10160 = (cljs.core._prefer_method[goog.typeOf(x__2391__auto____10159)]);
if(or__3824__auto____10160)
{return or__3824__auto____10160;
} else
{var or__3824__auto____10161 = (cljs.core._prefer_method["_"]);
if(or__3824__auto____10161)
{return or__3824__auto____10161;
} else
{throw cljs.core.missing_protocol.call(null,"IMultiFn.-prefer-method",mf);
}
}
})().call(null,mf,dispatch_val,dispatch_val_y);
}
});
cljs.core._get_method = (function _get_method(mf,dispatch_val){
if((function (){var and__3822__auto____10166 = mf;
if(and__3822__auto____10166)
{return mf.cljs$core$IMultiFn$_get_method$arity$2;
} else
{return and__3822__auto____10166;
}
})())
{return mf.cljs$core$IMultiFn$_get_method$arity$2(mf,dispatch_val);
} else
{var x__2391__auto____10167 = (((mf == null))?null:mf);
return (function (){var or__3824__auto____10168 = (cljs.core._get_method[goog.typeOf(x__2391__auto____10167)]);
if(or__3824__auto____10168)
{return or__3824__auto____10168;
} else
{var or__3824__auto____10169 = (cljs.core._get_method["_"]);
if(or__3824__auto____10169)
{return or__3824__auto____10169;
} else
{throw cljs.core.missing_protocol.call(null,"IMultiFn.-get-method",mf);
}
}
})().call(null,mf,dispatch_val);
}
});
cljs.core._methods = (function _methods(mf){
if((function (){var and__3822__auto____10174 = mf;
if(and__3822__auto____10174)
{return mf.cljs$core$IMultiFn$_methods$arity$1;
} else
{return and__3822__auto____10174;
}
})())
{return mf.cljs$core$IMultiFn$_methods$arity$1(mf);
} else
{var x__2391__auto____10175 = (((mf == null))?null:mf);
return (function (){var or__3824__auto____10176 = (cljs.core._methods[goog.typeOf(x__2391__auto____10175)]);
if(or__3824__auto____10176)
{return or__3824__auto____10176;
} else
{var or__3824__auto____10177 = (cljs.core._methods["_"]);
if(or__3824__auto____10177)
{return or__3824__auto____10177;
} else
{throw cljs.core.missing_protocol.call(null,"IMultiFn.-methods",mf);
}
}
})().call(null,mf);
}
});
cljs.core._prefers = (function _prefers(mf){
if((function (){var and__3822__auto____10182 = mf;
if(and__3822__auto____10182)
{return mf.cljs$core$IMultiFn$_prefers$arity$1;
} else
{return and__3822__auto____10182;
}
})())
{return mf.cljs$core$IMultiFn$_prefers$arity$1(mf);
} else
{var x__2391__auto____10183 = (((mf == null))?null:mf);
return (function (){var or__3824__auto____10184 = (cljs.core._prefers[goog.typeOf(x__2391__auto____10183)]);
if(or__3824__auto____10184)
{return or__3824__auto____10184;
} else
{var or__3824__auto____10185 = (cljs.core._prefers["_"]);
if(or__3824__auto____10185)
{return or__3824__auto____10185;
} else
{throw cljs.core.missing_protocol.call(null,"IMultiFn.-prefers",mf);
}
}
})().call(null,mf);
}
});
cljs.core._dispatch = (function _dispatch(mf,args){
if((function (){var and__3822__auto____10190 = mf;
if(and__3822__auto____10190)
{return mf.cljs$core$IMultiFn$_dispatch$arity$2;
} else
{return and__3822__auto____10190;
}
})())
{return mf.cljs$core$IMultiFn$_dispatch$arity$2(mf,args);
} else
{var x__2391__auto____10191 = (((mf == null))?null:mf);
return (function (){var or__3824__auto____10192 = (cljs.core._dispatch[goog.typeOf(x__2391__auto____10191)]);
if(or__3824__auto____10192)
{return or__3824__auto____10192;
} else
{var or__3824__auto____10193 = (cljs.core._dispatch["_"]);
if(or__3824__auto____10193)
{return or__3824__auto____10193;
} else
{throw cljs.core.missing_protocol.call(null,"IMultiFn.-dispatch",mf);
}
}
})().call(null,mf,args);
}
});
cljs.core.do_dispatch = (function do_dispatch(mf,dispatch_fn,args){
var dispatch_val__10196 = cljs.core.apply.call(null,dispatch_fn,args);
var target_fn__10197 = cljs.core._get_method.call(null,mf,dispatch_val__10196);
if(cljs.core.truth_(target_fn__10197))
{} else
{throw (new Error([cljs.core.str("No method in multimethod '"),cljs.core.str(cljs.core.name),cljs.core.str("' for dispatch value: "),cljs.core.str(dispatch_val__10196)].join('')));
}
return cljs.core.apply.call(null,target_fn__10197,args);
});

/**
* @constructor
*/
cljs.core.MultiFn = (function (name,dispatch_fn,default_dispatch_val,hierarchy,method_table,prefer_table,method_cache,cached_hierarchy){
this.name = name;
this.dispatch_fn = dispatch_fn;
this.default_dispatch_val = default_dispatch_val;
this.hierarchy = hierarchy;
this.method_table = method_table;
this.prefer_table = prefer_table;
this.method_cache = method_cache;
this.cached_hierarchy = cached_hierarchy;
this.cljs$lang$protocol_mask$partition0$ = 4194304;
this.cljs$lang$protocol_mask$partition1$ = 64;
})
cljs.core.MultiFn.cljs$lang$type = true;
cljs.core.MultiFn.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/MultiFn");
});
cljs.core.MultiFn.prototype.cljs$core$IHash$_hash$arity$1 = (function (this$){
var this__10198 = this;
return goog.getUid(this$);
});
cljs.core.MultiFn.prototype.cljs$core$IMultiFn$_reset$arity$1 = (function (mf){
var this__10199 = this;
cljs.core.swap_BANG_.call(null,this__10199.method_table,(function (mf){
return cljs.core.ObjMap.EMPTY;
}));
cljs.core.swap_BANG_.call(null,this__10199.method_cache,(function (mf){
return cljs.core.ObjMap.EMPTY;
}));
cljs.core.swap_BANG_.call(null,this__10199.prefer_table,(function (mf){
return cljs.core.ObjMap.EMPTY;
}));
cljs.core.swap_BANG_.call(null,this__10199.cached_hierarchy,(function (mf){
return null;
}));
return mf;
});
cljs.core.MultiFn.prototype.cljs$core$IMultiFn$_add_method$arity$3 = (function (mf,dispatch_val,method){
var this__10200 = this;
cljs.core.swap_BANG_.call(null,this__10200.method_table,cljs.core.assoc,dispatch_val,method);
cljs.core.reset_cache.call(null,this__10200.method_cache,this__10200.method_table,this__10200.cached_hierarchy,this__10200.hierarchy);
return mf;
});
cljs.core.MultiFn.prototype.cljs$core$IMultiFn$_remove_method$arity$2 = (function (mf,dispatch_val){
var this__10201 = this;
cljs.core.swap_BANG_.call(null,this__10201.method_table,cljs.core.dissoc,dispatch_val);
cljs.core.reset_cache.call(null,this__10201.method_cache,this__10201.method_table,this__10201.cached_hierarchy,this__10201.hierarchy);
return mf;
});
cljs.core.MultiFn.prototype.cljs$core$IMultiFn$_get_method$arity$2 = (function (mf,dispatch_val){
var this__10202 = this;
if(cljs.core._EQ_.call(null,cljs.core.deref.call(null,this__10202.cached_hierarchy),cljs.core.deref.call(null,this__10202.hierarchy)))
{} else
{cljs.core.reset_cache.call(null,this__10202.method_cache,this__10202.method_table,this__10202.cached_hierarchy,this__10202.hierarchy);
}
var temp__3971__auto____10203 = cljs.core.deref.call(null,this__10202.method_cache).call(null,dispatch_val);
if(cljs.core.truth_(temp__3971__auto____10203))
{var target_fn__10204 = temp__3971__auto____10203;
return target_fn__10204;
} else
{var temp__3971__auto____10205 = cljs.core.find_and_cache_best_method.call(null,this__10202.name,dispatch_val,this__10202.hierarchy,this__10202.method_table,this__10202.prefer_table,this__10202.method_cache,this__10202.cached_hierarchy);
if(cljs.core.truth_(temp__3971__auto____10205))
{var target_fn__10206 = temp__3971__auto____10205;
return target_fn__10206;
} else
{return cljs.core.deref.call(null,this__10202.method_table).call(null,this__10202.default_dispatch_val);
}
}
});
cljs.core.MultiFn.prototype.cljs$core$IMultiFn$_prefer_method$arity$3 = (function (mf,dispatch_val_x,dispatch_val_y){
var this__10207 = this;
if(cljs.core.truth_(cljs.core.prefers_STAR_.call(null,dispatch_val_x,dispatch_val_y,this__10207.prefer_table)))
{throw (new Error([cljs.core.str("Preference conflict in multimethod '"),cljs.core.str(this__10207.name),cljs.core.str("': "),cljs.core.str(dispatch_val_y),cljs.core.str(" is already preferred to "),cljs.core.str(dispatch_val_x)].join('')));
} else
{}
cljs.core.swap_BANG_.call(null,this__10207.prefer_table,(function (old){
return cljs.core.assoc.call(null,old,dispatch_val_x,cljs.core.conj.call(null,cljs.core._lookup.call(null,old,dispatch_val_x,cljs.core.PersistentHashSet.EMPTY),dispatch_val_y));
}));
return cljs.core.reset_cache.call(null,this__10207.method_cache,this__10207.method_table,this__10207.cached_hierarchy,this__10207.hierarchy);
});
cljs.core.MultiFn.prototype.cljs$core$IMultiFn$_methods$arity$1 = (function (mf){
var this__10208 = this;
return cljs.core.deref.call(null,this__10208.method_table);
});
cljs.core.MultiFn.prototype.cljs$core$IMultiFn$_prefers$arity$1 = (function (mf){
var this__10209 = this;
return cljs.core.deref.call(null,this__10209.prefer_table);
});
cljs.core.MultiFn.prototype.cljs$core$IMultiFn$_dispatch$arity$2 = (function (mf,args){
var this__10210 = this;
return cljs.core.do_dispatch.call(null,mf,this__10210.dispatch_fn,args);
});
cljs.core.MultiFn;
cljs.core.MultiFn.prototype.call = (function() { 
var G__10212__delegate = function (_,args){
var self__10211 = this;
return cljs.core._dispatch.call(null,self__10211,args);
};
var G__10212 = function (_,var_args){
var args = null;
if (goog.isDef(var_args)) {
  args = cljs.core.array_seq(Array.prototype.slice.call(arguments, 1),0);
} 
return G__10212__delegate.call(this, _, args);
};
G__10212.cljs$lang$maxFixedArity = 1;
G__10212.cljs$lang$applyTo = (function (arglist__10213){
var _ = cljs.core.first(arglist__10213);
var args = cljs.core.rest(arglist__10213);
return G__10212__delegate(_, args);
});
G__10212.cljs$lang$arity$variadic = G__10212__delegate;
return G__10212;
})()
;
cljs.core.MultiFn.prototype.apply = (function (_,args){
var self__10214 = this;
return cljs.core._dispatch.call(null,self__10214,args);
});
/**
* Removes all of the methods of multimethod.
*/
cljs.core.remove_all_methods = (function remove_all_methods(multifn){
return cljs.core._reset.call(null,multifn);
});
/**
* Removes the method of multimethod associated with dispatch-value.
*/
cljs.core.remove_method = (function remove_method(multifn,dispatch_val){
return cljs.core._remove_method.call(null,multifn,dispatch_val);
});
/**
* Causes the multimethod to prefer matches of dispatch-val-x over dispatch-val-y
* when there is a conflict
*/
cljs.core.prefer_method = (function prefer_method(multifn,dispatch_val_x,dispatch_val_y){
return cljs.core._prefer_method.call(null,multifn,dispatch_val_x,dispatch_val_y);
});
/**
* Given a multimethod, returns a map of dispatch values -> dispatch fns
*/
cljs.core.methods$ = (function methods$(multifn){
return cljs.core._methods.call(null,multifn);
});
/**
* Given a multimethod and a dispatch value, returns the dispatch fn
* that would apply to that value, or nil if none apply and no default
*/
cljs.core.get_method = (function get_method(multifn,dispatch_val){
return cljs.core._get_method.call(null,multifn,dispatch_val);
});
/**
* Given a multimethod, returns a map of preferred value -> set of other values
*/
cljs.core.prefers = (function prefers(multifn){
return cljs.core._prefers.call(null,multifn);
});

/**
* @constructor
*/
cljs.core.UUID = (function (uuid){
this.uuid = uuid;
this.cljs$lang$protocol_mask$partition1$ = 0;
this.cljs$lang$protocol_mask$partition0$ = 543162368;
})
cljs.core.UUID.cljs$lang$type = true;
cljs.core.UUID.cljs$lang$ctorPrSeq = (function (this__2337__auto__){
return cljs.core.list.call(null,"cljs.core/UUID");
});
cljs.core.UUID.prototype.cljs$core$IHash$_hash$arity$1 = (function (this$){
var this__10215 = this;
return goog.string.hashCode(cljs.core.pr_str.call(null,this$));
});
cljs.core.UUID.prototype.cljs$core$IPrintable$_pr_seq$arity$2 = (function (_10217,_){
var this__10216 = this;
return cljs.core.list.call(null,[cljs.core.str("#uuid \""),cljs.core.str(this__10216.uuid),cljs.core.str("\"")].join(''));
});
cljs.core.UUID.prototype.cljs$core$IEquiv$_equiv$arity$2 = (function (_,other){
var this__10218 = this;
var and__3822__auto____10219 = cljs.core.instance_QMARK_.call(null,cljs.core.UUID,other);
if(and__3822__auto____10219)
{return (this__10218.uuid === other.uuid);
} else
{return and__3822__auto____10219;
}
});
cljs.core.UUID.prototype.toString = (function (){
var this__10220 = this;
var this__10221 = this;
return cljs.core.pr_str.call(null,this__10221);
});
cljs.core.UUID;
