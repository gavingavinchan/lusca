//Initiation

const thrusterControl = require("./thrusterControl.js");
const HFL = new thrusterControl({name:"HFL", address: 0x39, invert: true}),
  HFR = new thrusterControl({name:"HFR", address: 0x30, invert: true}),
  HRL = new thrusterControl({name:"HRL", address: 0x37, invert: false}),
  HRR = new thrusterControl({name:"HRR", address: 0x36, invert: false}),
  VF = new thrusterControl({name:"VF", address: 0x3A, invert: false}),
  VR = new thrusterControl({name:"VR", address: 0x3E, invert: true}),
  SILO = new thrusterControl({name:"silo", address: 0x2D, invert: false});

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

var servoControl = require("./servoControl.js");
servoControl.init(0x17);

//const EMControl = require("./EMControl.js");
//const EM1 = new EMControl({name: 'EM1', address: 0x14});
//const EM2 = new EMControl({name: 'EM2', address: 0x16});


const EMmotorcontrol = require("./EMmotorcontrol.js");
const EM1 = new EMmotorcontrol({name: 'EM1', address: 0x11});
const EM2 = new EMmotorcontrol({name: 'EM2', address: 0x12});

var ds4Control = require("./ds4Control.js");


//TODO fix too many listener problem
var statusDisplay = require("./statusDisplayNEW.js");
statusDisplay.init();

var pHTemp = require("./pHTemp.js");
pHTemp.init(0x35);

//Program initiation time
io.emit('initiationTime', new Date(Date. UTC(0,0,0,0,0,0)));




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
};
