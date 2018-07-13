console.log("program is running");

//Express setup
var express = require("express");
var app = express();

//Creates server
var server = app.listen(8080, function(){
	console.log("listening to port 8080");
})

//Socket.io setup
var socket = require('socket.io');
var io = socket(server);

//Serialport setup
var SerialPort = require("serialport");
var port = new SerialPort(process.argv[2]);

//Displays the index.html page in the public folder
app.use(express.static('public'));

//Tells if the user is connected to the serial port
port.on('open', () => {
	console.log("arduino connected COM3");
})
//prints data sent from arduino to console
port.on('data', (data) => {
	console.log(data.toString());
});

//tells the servos to move depending on what button was pressed 
io.on('connection', (socket) => {
	console.log("socket connection made");

	//code for x-axis/base servo
	socket.on('startLeft', function(){
		console.log("started left");
		//add code to turn the x-axis/base servo left
		port.write('6');

	})
	socket.on('startRight', function(){
		console.log("started right");
		//add code to move the x-axis/base servo right
		port.write('5');
	})
	socket.on('stopLeft', function(){
		console.log("stopped left")
		//add code to turn the x-axis/base servo left
		port.write('0');
	})
	socket.on('stopRight', function(){
		console.log("stopped right");
		//add code to move the x-axis/base servo right
		port.write('0');
	})


	//code for y-axis (1)
	socket.on('startDown1', function(){
		console.log("y-axis (1) down started");
		//add code to move y-axis (1) servo down
		port.write("1");
	})
	socket.on('startUp1', function(){
		console.log('y-axis (1) up started');
		port.write("2");
	})
	socket.on('stopUp1', function(){
		console.log("y-axis (1) up stopped")
		port.write("0");
	})
	socket.on('stopDown1', function(){
		console.log("y-axis (1) down stopped")
		port.write("0");
	})


	//code for y-axis (2)
	socket.on('startDown2', function(){
		console.log("y-axis (2) down started");
		//add code to move y-axis (2) servo down
		port.write("3");
	})
	socket.on('startUp2', function(){
		console.log('y-axis (2) up started');
		//add code to move y-axis (2) servo up
		port.write("4");
	})
	socket.on('stopUp2', function(){
		console.log("y-axis (2) up stopped")
		port.write("0");
	})
	socket.on('stopDown2', function(){
		console.log("y-axis (2) down stopped")
		port.write("0");
	})


	//code for claw
	socket.on("closeClaw", function(){
		console.log("claw closed");
		//add code to close claw
		port.write('8');
	});
	socket.on("openClaw", function(){
		console.log("claw opened");
		//add code to close claw
		port.write('7');
	});

});

