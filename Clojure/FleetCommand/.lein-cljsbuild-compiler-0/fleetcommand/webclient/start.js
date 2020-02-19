goog.provide('fleetcommand.webclient.start');
goog.require('cljs.core');
goog.require('goog.net.Jsonp');
goog.require('goog.net.XhrIo');
goog.require('goog.events.KeyCodes');
goog.require('goog.events.KeyHandler');
goog.require('goog.events');
goog.require('goog.dom');
goog.require('fleetcommand.webclient.entity');
goog.require('fleetcommand.webclient.model');
goog.require('fleetcommand.webclient.renderer');
fleetcommand.webclient.start.keypress = (function keypress(event){
var key__16881 = event.keyCode;
return console.log(key__16881);
});
fleetcommand.webclient.start.start = (function start(){
return fleetcommand.webclient.model.get_all_models.call(null);
});
goog.exportSymbol('fleetcommand.webclient.start.start', fleetcommand.webclient.start.start);
fleetcommand.webclient.start.init_battle = (function init_battle(){
var jsonp__16883 = (new goog.net.Jsonp([cljs.core.str("/init/0")].join('')));
return jsonp__16883.send(null,null,null);
});
fleetcommand.webclient.start.render = (function render(){
var jsonp__16885 = (new goog.net.Jsonp([cljs.core.str("/get/0")].join('')));
return jsonp__16885.send(null,null,null);
});
goog.exportSymbol('fleetcommand.webclient.start.render', fleetcommand.webclient.start.render);
fleetcommand.webclient.start.get_battle_callback = (function get_battle_callback(reply){
fleetcommand.webclient.entity.render_all.call(null,reply.entities);
return setTimeout(fleetcommand.webclient.start.render,1000);
});
goog.exportSymbol('fleetcommand.webclient.start.get_battle_callback', fleetcommand.webclient.start.get_battle_callback);
fleetcommand.webclient.start.game_loop = (function game_loop(){
var document__16888 = goog.dom.getDocument();
var handler__16889 = (new goog.events.KeyHandler(document__16888,true));
goog.events.listen(handler__16889,"key",(function (e){
return fleetcommand.webclient.start.keypress.call(null,e);
}));
fleetcommand.webclient.renderer.init.call(null);
fleetcommand.webclient.start.render.call(null);
return console.log("End of game-loop");
});
goog.exportSymbol('fleetcommand.webclient.start.game_loop', fleetcommand.webclient.start.game_loop);
fleetcommand.webclient.start.init_battle_callback = (function init_battle_callback(reply){
return fleetcommand.webclient.start.game_loop.call(null);
});
goog.exportSymbol('fleetcommand.webclient.start.init_battle_callback', fleetcommand.webclient.start.init_battle_callback);
