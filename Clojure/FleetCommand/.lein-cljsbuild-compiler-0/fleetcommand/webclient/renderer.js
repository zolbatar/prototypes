goog.provide('fleetcommand.webclient.renderer');
goog.require('cljs.core');
goog.require('goog.graphics');
goog.require('goog.dom');
fleetcommand.webclient.renderer.width = cljs.core.atom.call(null,0);
fleetcommand.webclient.renderer.height = cljs.core.atom.call(null,0);
fleetcommand.webclient.renderer.canvas = cljs.core.atom.call(null,null);
fleetcommand.webclient.renderer.g = cljs.core.atom.call(null,null);
fleetcommand.webclient.renderer.edge_stroke = (new goog.graphics.Stroke(1,"#111"));
fleetcommand.webclient.renderer.back_stroke = (new goog.graphics.Stroke(0,"#FFF"));
fleetcommand.webclient.renderer.back_fill = (new goog.graphics.Fill(1,"#111"));
fleetcommand.webclient.renderer.get_size = (function get_size(){
cljs.core.reset_BANG_.call(null,fleetcommand.webclient.renderer.canvas,goog.dom.getElement("container"));
cljs.core.reset_BANG_.call(null,fleetcommand.webclient.renderer.width,cljs.core.deref.call(null,fleetcommand.webclient.renderer.canvas).clientWidth);
return cljs.core.reset_BANG_.call(null,fleetcommand.webclient.renderer.height,cljs.core.deref.call(null,fleetcommand.webclient.renderer.canvas).clientHeight);
});
fleetcommand.webclient.renderer.init = (function init(){
console.log("Initialising canvas...");
cljs.core.reset_BANG_.call(null,fleetcommand.webclient.renderer.g,(function (){var G__31115__31116 = goog.graphics.createGraphics("100%","100%");
G__31115__31116.render(goog.dom.getElement("container"));
return G__31115__31116;
})());
fleetcommand.webclient.renderer.get_size.call(null);
console.log([cljs.core.str("Width: "),cljs.core.str(cljs.core.deref.call(null,fleetcommand.webclient.renderer.width))].join(''));
return console.log([cljs.core.str("Height: "),cljs.core.str(cljs.core.deref.call(null,fleetcommand.webclient.renderer.height))].join(''));
});
fleetcommand.webclient.renderer.clear = (function clear(){
return cljs.core.deref.call(null,fleetcommand.webclient.renderer.g).clear();
});
fleetcommand.webclient.renderer.render_points = (function render_points(points,x,y,rot){
var path__31126 = (new goog.graphics.Path());
var t__31127 = (new goog.graphics.AffineTransform());
var f__31128 = cljs.core.first.call(null,points);
path__31126.moveTo(cljs.core.first.call(null,f__31128),cljs.core.second.call(null,f__31128));
var G__31129__31130 = cljs.core.seq.call(null,cljs.core.rest.call(null,points));
if(G__31129__31130)
{var p__31131 = cljs.core.first.call(null,G__31129__31130);
var G__31129__31132 = G__31129__31130;
while(true){
path__31126.lineTo(cljs.core.first.call(null,p__31131),cljs.core.second.call(null,p__31131));
var temp__3974__auto____31133 = cljs.core.next.call(null,G__31129__31132);
if(temp__3974__auto____31133)
{var G__31129__31134 = temp__3974__auto____31133;
{
var G__31135 = cljs.core.first.call(null,G__31129__31134);
var G__31136 = G__31129__31134;
p__31131 = G__31135;
G__31129__31132 = G__31136;
continue;
}
} else
{}
break;
}
} else
{}
path__31126.close();
t__31127.translate(x,y);
t__31127.rotate(rot,0,0);
path__31126.transform(t__31127);
return cljs.core.deref.call(null,fleetcommand.webclient.renderer.g).drawPath(path__31126,fleetcommand.webclient.renderer.edge_stroke);
});
