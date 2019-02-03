var i2c = require('i2c');
device = new i2c(0x70, {device: '/dev/i2c-1'});

function ping(){
  device.readBytes(0x99, 2, function(err,res) {
    if (err){
      console.log("error reading" + err);
      return;
    }
    pingResults = res;
    console.log(res[0] + "\t" + res[1]);
  });
}

setInterval(ping, 10);
