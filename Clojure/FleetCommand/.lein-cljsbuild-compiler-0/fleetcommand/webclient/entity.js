goog.provide('fleetcommand.webclient.entity');
goog.require('cljs.core');
goog.require('fleetcommand.webclient.js_helper');
goog.require('fleetcommand.webclient.renderer');
goog.require('fleetcommand.webclient.model');
fleetcommand.webclient.entity.entities = cljs.core.atom.call(null,null);
fleetcommand.webclient.entity.clear = (function clear(){
return cljs.core.reset_BANG_.call(null,fleetcommand.webclient.entity.entities,cljs.core.ObjMap.EMPTY);
});
fleetcommand.webclient.entity.render = (function render(entity){
return fleetcommand.webclient.model.render.call(null,entity.modelid,entity.x,entity.y,entity.rot);
});
fleetcommand.webclient.entity.render_all = (function render_all(entities_in){
fleetcommand.webclient.renderer.clear.call(null);
cljs.core.reset_BANG_.call(null,fleetcommand.webclient.entity.entities,entities_in);
var time__27584 = fleetcommand.webclient.js_helper.get_time.call(null);
var n__2555__auto____27585 = cljs.core.count.call(null,entities_in);
var x__27586 = 0;
while(true){
if((x__27586 < n__2555__auto____27585))
{var entity__27587 = cljs.core.nth.call(null,entities_in,x__27586);
fleetcommand.webclient.entity.render.call(null,entity__27587);
{
var G__27588 = (x__27586 + 1);
x__27586 = G__27588;
continue;
}
} else
{}
break;
}
return console.log([cljs.core.str("Rendering took "),cljs.core.str((fleetcommand.webclient.js_helper.get_time.call(null) - time__27584)),cljs.core.str("ms")].join(''));
});
