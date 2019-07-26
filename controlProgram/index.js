//Initiation

const thrusterControl = require("./thrusterControl.js");
const HFL = new thrusterControl({name:"HFL", address: 0x38, invert: true}),
  HFR = new thrusterControl({name:"HFR", address: 0x31, invert: true}),
  HRL = new thrusterControl({name:"HRL", address: 0x33, invert: false}),
  HRR = new thrusterControl({name:"HRR", address: 0x39, invert: false}),
  VF = new thrusterControl({name:"VF", address: 0x3E, invert: true}),
  VR = new thrusterControl({name:"VR", address: 0x3A, invert: false}),
  SILO = new thrusterControl({name:"silo", address: 0x2D, invert: false});

var _messenger = require("./messenger.js");
//_messenger.startServer();
var messenger = new _messenger.client({});

var thrustProfile = require("./thrustProfile6T.js");

var cameraControl = require("./servoControl.js");
cameraControl.init(0x17);

const EMmotorcontrol = require("./EMmotorcontrol.js");
const EM1 = new EMmotorcontrol({name: 'EM1', address: 0x11});
const EM2 = new EMmotorcontrol({name: 'EM2', address: 0x12});

var ds4Control = require("./ds4ControlAlt.js");

//TODO fix too many listener problem
var statusDisplay = require("./statusDisplayNEW.js");
statusDisplay.init();

var pHTemp = require("./pHTemp.js");
pHTemp.init(0x35);

//Program initiation time
messenger.emit('initiationTime', new Date(Date. UTC(0,0,0,0,0,0)));
