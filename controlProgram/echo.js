var i2c = require('i2c');

var io = require('socket.io-client');
var socket = io.connect('http://localhost:80');


exports.init = function(echoerAddr) {
  console.log("echoerAddr: " +echoerAddr);
  var device = new i2c(echoerAddr, {device: '/dev/i2c-1'});

  var lastSentTime = new Date();
  function roundTripTime() {
    var currentTime = new Date();
    var _runTimeMillis = currentTime - lastSentTime;
    //console.log("runTimeMillis: " + _runTimeMillis);
    return _runTimeMillis;
  }


  function echo() {
    //send time
    lastSentTime = new Date();
    var hbSend = lastSentTime>>8 & 0xFF;
    var lbSend = lastSentTime & 0xFF;

    device.writeBytes(0x90,[hbSend, lbSend], function(err) {
      if (err) {
        var errorMessage = "error writing " + err;
        socket.emit('echoerError', errorMessage);
        console.log("error reading" + err);
        return;
      }
      device.readBytes(0x90, 2, function(rerr, res){
        if (rerr){
           socket.emit('echoerError', rerr);
           return;
        }
        if ((res[0]!=hbSend) || (res[1] !=lbSend) ){
           socket.emit('echoerError', 'error in echo resposne');
           return;
        }
        socket.emit('echoerRoundTime', roundTripTime()+'');
      });
    });
  }

  socket.on('echo', function() {
    echo();
  });
}

