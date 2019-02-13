var i2c = require('i2c');
device = new i2c(0x14, {device: '/dev/i2c-1'});

var pingResults = [];
function ping(){
/*
  device.readBytes(0x99, 1, function(err,res) {
    if (err){
      console.log("error reading" + err);
      return;
    }
    pingResults[0] = res[0];
    //console.log(res[0] + "\t" + res[1]);
  });

  device.readBytes(0x99, 1, function(err,res) {
    if (err){
      console.log("error reading" + err);
      return;
    }
    pingResults[1] = res[0];
    //console.log(res[0] + "\t" + res[1]);
  });

  console.log(pingResults[0] + "\t" + pingResults[1]);
*/

  device.write([0x99], function(err) {
    if (err){
      console.log("error reading" + err);
      return;
    }
  });

  device.read(1, function(err,res) {
    if (err){
      console.log("error reading" + err);
      return;
    }
    console.log(res[0]);
  });


  device.read(1, function(err,res) {
    if (err){
      console.log("error reading" + err);
      return;
    }
    console.log("\t" + res[0]);
  });


}

setInterval(ping, 10);
