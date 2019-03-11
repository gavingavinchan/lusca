var i2c = require('i2c');

var io = require('socket.io-client');
var socket = io.connect('http://localhost:80');

//default resistor values
var resistor1 = 1000;  //resistor connected between 12V and the pin
var resistor2 = 100;   //resistor connected between pin and GND


exports.init = function(pingerAddr) {
  device = new i2c(pingerAddr, {device: '/dev/i2c-1'});


  // measured values of actual resistors
  if(pingerAddr == 0x14) {
    resistor1 = 1001;
    resistor2 = 100.2;
  }
}


var pingResults = [];
var sourceVoltage = 0;
socket.on('Ping', function() {
  ping();
 // console.log("ping: " + pingResults);
  var raw = (pingResults[0]<<8) | (pingResults[1]);
  pinVoltage = raw/1024*5;
  sourceVoltage = pinVoltage*(resistor1+resistor2)/resistor2;

  socket.emit('pingerPinVoltage', pinVoltage);
  socket.emit('pingerSourceVoltage', sourceVoltage);

/*
    console.log(res[0] + "\t" + res[1]);
    var raw = (pingResults[0]<<8) | (pingResults[1]);
    pinVoltage = raw/1024*5;
    inputVoltage = raw/1024*12;
    socket.emit('pingerPinVoltage', pinVoltage);
    socket.emit('pingerInputVoltage', inputVoltage);
    */
})




function ping() {
  device.readBytes(0x99, 2, function(err,res) {
    if (err){
      var errorMessage = "error reading" + err;
      socket.emit('pingerError', errorMessage);
      return;
    }
    pingResults[0] = res[0];
    pingResults[1] = res[1];
  })


  /*
  device.write([0x99], function(err) {
    if (err){
      var errorMessage = "error reading" + err;
      socket.emit('pingerError', errorMessage);
      //console.log("error reading" + err);
      return;
    }
  });

  device.read(1, function(err,res) {
    if (err){
      var errorMessage = "error reading" + err;
      socket.emit('pingerError', errorMessage);
      return;
    }
    pingResults[0] = res[0];
  });


  device.read(1, function(err,res) {
    if (err){
      var errorMessage = "error reading" + err;
      socket.emit('pingerError', errorMessage);
      return;
    }
    pingResults[1] = res[0];
  });

*/
}

//setInterval(ping, 50);
