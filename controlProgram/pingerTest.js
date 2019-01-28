var i2c = require('i2c');
device = new i2c(0x70, {device: '/dev/i2c-1'});

function ping(){
  device.readBytes(0x95, 4, function(err,res) {
    if (err){
      console.log("error reading" + err);
      return;
    }
    pingResults = res;
    if(res[2]==0x00 && res[3]==0xFF){
      console.log(res[0] + "\t" + res[1]);
    }
    else{
      console.log(res[0]+"\t"+res[1]+"\t"+res[2]+"\t"+res[3]);
    }
  });
}

setInterval(ping, 200);
