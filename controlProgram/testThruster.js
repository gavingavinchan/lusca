var i2c = require('i2c');
const interval = require('interval-promise');
var us = require('microseconds');

addrs = [0x31, 0x32, 0x33, 0x30, 0x3A, 0x3B]//, 0x31]//, 0x31, 0x3A, 0x3B]//, 0x3A, 0x3B];

thrusters = [];
for(var a of addrs){
	thrusters.push(new i2c(a, {device:'/dev/i2c-3'}));
}

voltage = new i2c(0x70, {device: '/dev/i2c-3'});

async function writeThruster(t, speed){
	return new Promise((resolve, reject)=>{
		var start = us.now();
		t.writeBytes(0x00, [speed*32767>>>8, (speed*32767)%255], function(err){
				if(err){
					reject(err);
				}else{
					// console.log(speed + "\t" + (us.now() - start));
					resolve();
				}
		});
	});
}

async function writeThrusters(speed){
	for (var t of thrusters){
		await writeThruster(t, speed);
	}
}

async function readVoltage(){
	return new Promise( (resolve, reject)=>{
		var start = us.now();
		voltage.readBytes(0x99, 2, (err, res) => {
			if (err){
				reject(err);
			}else{
				let adc = (res[0]<<8) + (0xff & res[1]);
				// let voltage = adc / 1024 * 5;
				// voltage = Math.round(voltage, 2);
				console.log( adc + "\t" + (us.now() - start) );
				resolve();
			}
		});
	});
}
var terror = 0, perror = 0;
interval(async(i) => {
	try{
		var begin = us.now();
		let tasks = [];
		if (i<5)
			await writeThrusters(0);
		else
			await writeThrusters( (i * 50));
	}catch(err){
		terror ++;
	}
	try{
		await readVoltage();
	}catch(err){
		perror ++;	
	}
	let total_time = (us.now() - begin)/1000;
	console.log("iteration: " + i + "\t time: " + total_time + " ms, error: " + terror + "\t" + perror);
}, 75, { iterations: 300 });

/*
interval(async() => {
	writeThrusters(2000);
}, 500, { iterations: 10 });

interval(async() => {
	writeThrusters(0);
}, 500, { iterations: 4 });*/
