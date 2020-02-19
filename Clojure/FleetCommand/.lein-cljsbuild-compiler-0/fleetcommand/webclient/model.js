goog.provide('fleetcommand.webclient.model');
goog.require('cljs.core');
goog.require('fleetcommand.webclient.renderer');

/**
* @constructor
*/
fleetcommand.webclient.model.Section = (function (id,points){
this.id = id;
this.points = points;
})
fleetcommand.webclient.model.Section.cljs$lang$type = true;
fleetcommand.webclient.model.Section.cljs$lang$ctorPrSeq = (function (this__2338__auto__){
return cljs.core.list.call(null,"fleetcommand.webclient.model/Section");
});
fleetcommand.webclient.model.Section;

/**
* @constructor
*/
fleetcommand.webclient.model.Model = (function (sections){
this.sections = sections;
})
fleetcommand.webclient.model.Model.cljs$lang$type = true;
fleetcommand.webclient.model.Model.cljs$lang$ctorPrSeq = (function (this__2338__auto__){
return cljs.core.list.call(null,"fleetcommand.webclient.model/Model");
});
fleetcommand.webclient.model.Model;
fleetcommand.webclient.model.models = cljs.core.atom.call(null,cljs.core.ObjMap.EMPTY);
fleetcommand.webclient.model.get_all_models_callback = (function get_all_models_callback(reply){
var G__20446__20447 = cljs.core.seq.call(null,reply.models);
if(G__20446__20447)
{var model__20448 = cljs.core.first.call(null,G__20446__20447);
var G__20446__20449 = G__20446__20447;
while(true){
var id__20450 = model__20448.id;
var geos__20451 = model__20448.geo;
var sections__20452 = cljs.core.doall.call(null,cljs.core.map.call(null,((function (model__20448,G__20446__20449){
return (function (p1__20436_SHARP_){
return (new fleetcommand.webclient.model.Section(p1__20436_SHARP_.id,p1__20436_SHARP_.points));
});})(model__20448,G__20446__20449))
,geos__20451));
cljs.core.swap_BANG_.call(null,fleetcommand.webclient.model.models,cljs.core.assoc,id__20450,(new fleetcommand.webclient.model.Model(sections__20452)));
var temp__3974__auto____20453 = cljs.core.next.call(null,G__20446__20449);
if(temp__3974__auto____20453)
{var G__20446__20454 = temp__3974__auto____20453;
{
var G__20455 = cljs.core.first.call(null,G__20446__20454);
var G__20456 = G__20446__20454;
model__20448 = G__20455;
G__20446__20449 = G__20456;
continue;
}
} else
{}
break;
}
} else
{}
return fleetcommand.webclient.start.init_battle.call(null);
});
goog.exportSymbol('fleetcommand.webclient.model.get_all_models_callback', fleetcommand.webclient.model.get_all_models_callback);
fleetcommand.webclient.model.get_all_models = (function get_all_models(){
var jsonp__20458 = (new goog.net.Jsonp([cljs.core.str("/models")].join('')));
return jsonp__20458.send(null,null,null);
});
fleetcommand.webclient.model.render = (function render(id,x,y,rot){
var model__20466 = cljs.core._lookup.call(null,cljs.core.deref.call(null,fleetcommand.webclient.model.models),id,null);
var G__20467__20468 = cljs.core.seq.call(null,model__20466.sections);
if(G__20467__20468)
{var section__20469 = cljs.core.first.call(null,G__20467__20468);
var G__20467__20470 = G__20467__20468;
while(true){
fleetcommand.webclient.renderer.render_points.call(null,section__20469.points,x,y,rot);
var temp__3974__auto____20471 = cljs.core.next.call(null,G__20467__20470);
if(temp__3974__auto____20471)
{var G__20467__20472 = temp__3974__auto____20471;
{
var G__20473 = cljs.core.first.call(null,G__20467__20472);
var G__20474 = G__20467__20472;
section__20469 = G__20473;
G__20467__20470 = G__20474;
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
