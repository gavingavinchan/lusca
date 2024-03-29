const PHM = 0.0168789808917;
const PHB = 0.1516;
const TEMPM = 0;
const TEMPB = 0;

//console.log('starting');
var i2c = require('i2c');
var io = require('socket.io-client');
var socket = io.connect('http://localhost:80');

var ads1x15 = require('node-ads1x15');
var adc = new ads1x15(1);

exports.init = function(pHTempAddr) {
  device = new i2c(pHTempAddr, {device: '/dev/i2c-1'});
  //console.log('initiate i2c');
};

var pHValue;
var tempValue;

var pHResult = [];
var tempResult = [];
var pHByte;
var tempByte;
socket.on('pHTemp', function(command) {
  //console.log('received command: ' + command);
  pHTemp();
  //send results
  if (command == 0x67) {
    //console.log('sending Bytes');
    socket.emit('pH Value', pHByte);
  } else if (command == 0x68) {
    //console.log('sending Bytes');
    socket.emit('Temp Value', tempByte);
  } else if (command == 0x69) {
    //console.log('sending Bytes');
    if (pHValue) {
      socket.emit('pH Value', pHByte);
      socket.emit('Temp Value', tempByte);
    } else {
      socket.emit('pH Value', -1);
      socket.emit('Temp Value', -1)
    }
  };
});


function unBitShift(result0, result1) {
  return (result0 << 8) | result1;
};


function pHTemp() {
  if(!adc.busy) {
    //A0 for pH
    adc.readADCSingleEnded(0, 4096, 250, function(err, data) {
      if(err) {
        var errorMessage = 'error reading: ' + err;
        socket.emit('miscError' + errorMessage);
        return;
      };

      pHByte = data;
     pHValue = (PHM * pHByte) + PHB;


    });
    //A2 for temperature
    adc.readADCSingleEnded(2, 4096, 250, function(err, data) {
      if(err) {
        var errorMessage = 'error reading: ' + err;
        socket.emit('miscError' + errorMessage);
        return;
      };

      tempByte = data;
      tempValue = (TEMPM * pHByte) + TEMPB;

    });
  };

  /*
  device.readBytes(0x69, 4, function(err, res) {
    if (err){
      var errorMessage = "error reading" + err;
      socket.emit('miscError: '+ errorMessage);
      return;
    };
    pHResult[0] = res[0];
    pHResult[1] = res[1];
    // console.log('pH Result: ' + pHResult);

    pHByte = unBitShift(pHResult[0], pHResult[1]);
    //console.log('pHByte: ' + pHByte);


    tempResult[0] = res[2];
    tempResult[1] = res[3];
    //console.log('Temp Result: ' + tempResult);

    tempByte = unBitShift(tempResult[0], tempResult[1]);
    //console.log('tempByte: ' + tempByte);

    pHValue = (PHM * pHByte) + PHB;
    tempValue = (TEMPM * tempByte) + TEMPB;
    */
};
