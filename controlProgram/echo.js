var i2c = require('i2c');

var io = require('socket.io-client');
var socket = io.connect('http://localhost:80');


exports.init = function(echoerAddr) {
  device = new i2c(echoerAddr, {device: '/dev/i2c-1'});
}


socket.on('echo', function() {
  echo();
});

/*
function i2cWrite(_byte) {
  device.write([_byte], function(err) {
    if (err) {
      var errorMessage = "error reading" + err;
      socket.emit('echoerError', errorMessage);
      //console.log("error reading" + err);
      return;
    }
  })
}

function i2cread() {
  device.read(1, function(err,res) {
    if (err) {
      var errorMessage = "error reading" + err;
      socket.emit('echoerError', errorMessage);
      console.log("echoerError: ", echoerError);
      return;
    }
    console.log("res[0]: " + res[0]);
    return res[0]
  });
}
*/


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

  device.writeBytes(0x90,[hbSend,lbSend], function(err) {
    if (err) {
      var errorMessage = "error reading" + err;
      socket.emit('echoerError', errorMessage);
      //console.log("error reading" + err);
      return;
    }
  });


  var hbReceive = 0;
  var lbReceive = 0;
  device.read(2,function(err,res) {
    if (err) {
      var errorMessage = "error reading" + err;
      socket.emit('echoerError', errorMessage);
      //console.log("error reading" + err);
      return;
    }
    hbReceive = res[0];
    lbReceive = res[1];
    //console.log('hbReceive: ' + hbReceive);
    //console.log('lbReceive: ' + lbReceive);
    var _roundTripTime = roundTripTime();

    //determine if have error
    if(hbSend != hbReceive) {
      socket.emit('echoerError', "High byte received not same as sent");
      return;
    }

    if(lbSend != lbReceive) {
      socket.emit('echoerError', "Low byte received not same as sent");
      return;
    }

    //calculate roundTime
    socket.emit('echoerRoundTime', (_roundTripTime).toString());
  });
}
