var i2c = require('i2c');

var io = require('socket.io-client');
var socket = io.connect('http://localhost:80');


exports.init = function(echoerAddr) {
  device = new i2c(echoerAddr, {device: '/dev/i2c-1'});
}


socket.on('echo', function() {
  echo();
});


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



var initiationTime = new Date();
socket.on('initiationTime', function(_time) {
  initiationTime = _time;
})

function runTimeMillis() {
  var currentTime = new Date();
  var  _runTimeMillis = currentTime - initiationTime;
  return _runTimeMillis;
}



function echo() {
  //send time
  var sendTime = runTimeMillis();
  var hbSend = sendTime>>8 & 0xFF;
  var lbSend = sendTime & 0xFF;

  device.write([0x90,hbSend,lbSend], function(err) {
    if (err) {
      var errorMessage = "error reading" + err;
      socket.emit('echoerError', errorMessage);
      //console.log("error reading" + err);
      return;
    }
  });


  //read hb
  var hbReceive = i2cread();
  console.log('hbReceive: ' + hbReceive)
  var receiveTime = runTimeMillis();

  //read lb
  var lbReceive = i2cread();
  console.log('lbReceive: ' + lbReceive)

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
  socket.emit('echoerRoundTime', (receiveTime-sendTime).toString());
}
