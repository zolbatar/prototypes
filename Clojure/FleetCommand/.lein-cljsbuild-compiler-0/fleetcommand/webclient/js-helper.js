goog.provide('fleetcommand.webclient.js_helper');
goog.require('cljs.core');
fleetcommand.webclient.js_helper.get_time = (function get_time(){
return (new Date()).getTime();
});
