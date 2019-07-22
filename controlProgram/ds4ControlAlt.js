const silo_pwr = 0.2;

var _messenger = require("./messenger.js");
var messenger = new _messenger.client({});

var HID = require('node-hid');
var devices = HID.devices();
//console.log(devices);

//THIS USES EDITED node-gamepad!!!
var GamePad = require("./node-gamepad/");
var controllerFound = false;
var controller;
for (let o of devices) {
  if(o.vendorId == 1356 && o.productId == 2508) {
    controller = new GamePad("ps4/dualshock4_analogBlueUnderbelly");
    controllerFound = true;
    break;
  }else if(o.vendorId == 1356 && o.productId == 1476) {
    controller = new GamePad("ps4/dualshock4_analog");
    controllerFound = true;
    break;
  }
}

if(!controllerFound) {
  messenger.emit('miscError', 'no controller found');
}



messenger.on('connect', ()=>{
    messenger.emit('thrusterControl.start', {});
});

var status = {
  gamepad: {
    leftX: 0,
    leftY: 0,
    rightX: 0,
    rightY: 0,
    l2: 0,
    r2: 0,
    direction: 1,
    XButton: false,
    fineControlToggle: false
  },
  thrust: {
    HL: 0,
    HR: 0,
    VL: 0,
    VR: 0,
    fineCoarse: "coarse",
  },
  manipulator: {
    EM1: {
      left: 0,
      right: 0,
    },
    EM2: {
      left: 0,
      right: 0,
    },
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
    ch1: false,
    ch2: false,
    ch3: false
  },
  message: []
};

//Thrusters
function normalize(x) {
  return (x - 255/2)/(255/2);
}

if(controllerFound) {
  controller.connect();


  controller.on("left:move", function(value) {
    let gp = status.gamepad;
    gp.leftX = normalize(value.x);
    gp.leftY = -normalize(value.y);

    messenger.emit('drive', gp.leftY);
    messenger.emit('strafe', gp.leftX);
  })

  controller.on("right:move", function(value) {
    let gp = status.gamepad;

    gp.rightX = normalize(value.x);
    gp.rightY = normalize(value.y);

    messenger.emit('rotate', gp.rightX);
    messenger.emit('tilt', gp.rightY);
  })


  controller.on("l2:change", function(value) {
    let gp = status.gamepad;
    gp.l2 = value/255;
    messenger.emit('upDown', gp.l2 - gp.r2);
  })

  controller.on("r2:change", function(value){
    let gp = status.gamepad;
    gp.r2 = value/255;
    messenger.emit('upDown', gp.l2 - gp.r2);
  })


  controller.on("circle:press", function() {
    status.gamepad.direction *= -1;
    messenger.emit('profile.direction', status.gamepad.direction);
  });

  controller.on("x:press", function() {
    if(status.thrust.fineCoarse == "fine") {
      status.thrust.fineCoarse = "medium";
    } else if(status.thrust.fineCoarse == "medium") {
      status.thrust.fineCoarse = "coarse";
    } else {
      status.thrust.fineCoarse = "fine";
    }

    messenger.emit('profile.fineCoarse', status.thrust.fineCoarse);
  })

  controller.on("share:press", function() {
    messenger.emit("thrusterTarget.silo", -silo_pwr);
  });

  controller.on("share:release", function(){
    messenger.emit("thrusterTarget.silo", 0.0);
  });

  controller.on("options:press", function() {
    messenger.emit("thrusterTarget.silo", silo_pwr);
  });

  controller.on("options:release", function(){
    messenger.emit("thrusterTarget.silo", 0.0 );
  });


function EMemit(_EM,_strength,_side,_boolean) {
  messenger.emit(_EM, {strength: _strength, side: _side, boolean: _boolean});
}

  //electromagnet
  controller.on("l1:press", function(){
    if(status.manipulator.EM1.left) {
      status.manipulator.EM1.left = false;

      EMemit("EM1",100,"left",status.manipulator.EM1.left);
      setTimeout(function() {
        EMemit("EM1",0,"left",status.manipulator.EM1.left);
      },500);
    } else {
      status.manipulator.EM1.left = true;
      EMemit("EM1",255,"left",status.manipulator.EM1.left);
    }
  });

  controller.on("r1:press", function(){
    if(status.manipulator.EM1.right) {
      status.manipulator.EM1.right = false;
      EMemit("EM1",100,"right",status.manipulator.EM1.right);
      setTimeout(function() {
        EMemit("EM1",0,"right",status.manipulator.EM1.right);
      },500);
    } else {
      status.manipulator.EM1.right = true;
      EMemit("EM1",255,"right",status.manipulator.EM1.right);
    }
  })


  controller.on("square:press", function(){
    if(status.manipulator.EM2.left) {
      status.manipulator.EM2.left = false;
      EMemit("EM2",154,"left",status.manipulator.EM2.left);
      setTimeout(function() {
        EMemit("EM2",0,"left",status.manipulator.EM2.left);
      },500);
    } else {
      status.manipulator.EM2.left = true;
      EMemit("EM2",1,"left",status.manipulator.EM2.left);
    }
  })

  controller.on("triangle:press", function(){
    if(status.manipulator.EM2.right) {
      status.manipulator.EM2.right = false;
      EMemit("EM2",154,"right",status.manipulator.EM2.right);
      setTimeout(function() {
        EMemit("EM2",0,"right",status.manipulator.EM2.right);
      },500);
    } else {
      status.manipulator.EM2.right = true;
      EMemit("EM2",1,"right",status.manipulator.EM2.right);
    }
  })

  //servo
  controller.on("dpadUp:press", function() {
    let _micros = 1500;
    if(status.video.ch1) {
      _micros = 1500;
      status.video.ch1 = false;
    } else {
      _micros = 1100;
      status.video.ch1 = true;
    }

    messenger.emit('servo', {command:0x11, micros: _micros});
    messenger.emit('CAM.ch1', status.video.ch1);
  })


  controller.on("dpadLeft:press", function() {
    let _micros = 1500;
    if(status.video.ch2) {
      _micros = 1500;
      status.video.ch2 = false;
    } else {
      _micros = 1100;
      status.video.ch2 = true;
    }

    messenger.emit('servo', {command:0x12, micros: _micros});
    messenger.emit('CAM.ch2', status.video.ch2);
  })

  controller.on("dpadDown:press", function() {
    let _micros = 1500;
    if(status.video.ch3) {
      _micros = 1500;
      status.video.ch3 = false;
    } else {
      _micros = 1100;
      status.video.ch3 = true;
    }

    messenger.emit('servo', {command:0x13, micros: _micros});
    messenger.emit('CAM.ch3', status.video.ch3);
  })

  var commandSender;
  controller.on("dpadRight:press",function() {
    messenger.emit('pHTemp',0x69);
  });
}




/*
setInterval(function() {
  // messenger.emit('Ping');
  //messenger.emit('echo');
  messenger.emit('pHTemp',0x69);
},1000);
*/
