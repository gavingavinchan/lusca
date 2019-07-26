var events = require('events');
const eventEmitter = new events.EventEmitter();


var client =  function(setting){
  //var io = require('socket.io-client');
  //var socket = io.connect('http://localhost:80');
  var c = function() {};

  //eventEmitter.on("message", function(_message) {console.log("a"); return _message;});

  c.on = function(channel, callback) {
      //var a = eventEmitter.on(channel, function(_message) {return _message;});
      //console.log(a);
      //return a;
      return eventEmitter.on(channel, callback);
   },

  c.emit = function(channel,message) {
    //console.log("emit " + channel + ": " + message);
    console.log("dummyMessenger emit message: " + message);
    return eventEmitter.emit(channel,message);
  }


  return c;
}


module.exports = {
  client : client,
  //startServer: server
}
