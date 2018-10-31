var DTMFpin = [0x06,0x01,0x03];

//Initiation

const thrusterControl = require("./thrusterControl.js");
const HFL = new thrusterControl({name:"HFL", address: 0x32, invert: true}),
  HFR = new thrusterControl({name:"HFR", address: 0x31, invert: true}),
  HRL = new thrusterControl({name:"HRL", address: 0x33, invert: false}),
  HRR = new thrusterControl({name:"HRR", address: 0x30, invert: false}),
  VF = new thrusterControl({name:"VF", address: 0x3A, invert: false}),
  VR = new thrusterControl({name:"VR", address: 0x3B, invert: true});

const express = require('express');
const app = express();
var http = require('http').Server(app);
var io = require('socket.io')(http);
app.use(express.static('public'));
app.get('/', (req, res) => {
	res.send('Hello Express app');
});


io.on('connection', function(socket) {
  // log socket communications
  /*
  socket.use((packet, next) => {
    console.log(new Date() + '\t' + packet[0] + '\t' + packet[1]);
    return next();
  });
*/

  // relay messages from clients
  socket.use((packet, next) => {
    io.emit(packet[0], packet[1]);
    return next();
  });
});

http.listen(80, function() {
  console.log('listening on *:80 ');
});

var thrustProfile = require("./thrustProfile6T.js");
/*
var servoControl = require("./servoControl.js");
servoControl.init(0x17);

const EMControl = require("./EMControl.js");
const EM1 = new EMControl({name: 'EM1', address: 0x14});
const EM2 = new EMControl({name: 'EM2', address: 0x16});

var DTMFencoder = require("./DTMFencoderControl.js");
DTMFencoder.init(0x20);

*/
var ds4Control = require("./ds4Control.js");

//TODO fix too many listener problem
var statusDisplay = require("./statusDisplayNEW.js");


var ms5803 = require('ms5803');
var sensor = new ms5803();



//io.emit('DTMFpin', DTMFpin);


//why was the statusDisplay disabled during the first water trial?
statusDisplay.init();

var status = {
  gamepad: {
    leftX: 0,
    leftY: 0,
    rightX: 0,
    rightY: 0,
    direction: 1,
    XButton: false,
    fineControlToggle: false
  },
  thrust: {
    HL: 0,
    HR: 0,
    VL: 0,
    VR: 0,
    fineCoarse: true,
  },
  manipulator: {
    EM1: false,
    EM2: false,
    DTMFencoder: 0    //0: not playing, 1: playing
  },
  depth: {
    raw: 0,
    mBar: 0,
    cm: 0,
    cmTared: 0,
    tare: 0,
    zero: 0,
  },
  video: {
    ch1: true,
    ch2: false
  },
  message: []
};

exports.getStatus = function() {
  return status;
}


//delay
function delay(ms){
  return new Promise( (resolve, reject) => {
      setTimeout( () => {
        resolve();
      }, ms);
  });
}


//depth sensor
sensor.reset(function(err) {
  if (err) {
    status.message = err;
    return;
  }
	sensor.begin(function(err, coefficient){

		setInterval( function(){
			sensor.measure(function(err, result){
        if(err) return;
        try{
	  if(result.temperature>50){ // likely a bug
		status.message = 'problem from sensor: temp: '+result.temperature;
		return;
          }
          status.depth.raw = result.pressure;
          status.depth.mBar = result.pressure - status.depth.zero;   //mBar, not tared
        //console.log(result);
          status.depth.cm = ((result.pressure - status.depth.zero)*100*100)/(1000*9.81); //cm, not tared

          status.depth.cmTared = ((result.pressure - status.depth.tare)*100*100)/(1000*9.81); //cm, tared
        }catch(exception){
          status.message = 'exception from depth sensor';
        }
			});
		}, 1000);
	});
});
