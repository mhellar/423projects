var com = require("serialport");
var express = require('express');
//create express object named app
var app = express();

var server = app.listen(3000);
var io = require('socket.io')(server);

const SerialPort = require("serialport");
const Readline = SerialPort.parsers.Readline;
const port = new SerialPort("/dev/cu.SLAB_USBtoUART", {
    baudRate: 9600
});

app.use(express.static('public'));

//Serve index.html when some make a request of the server
app.get('/', function (req, res) {
    res.sendFile(__dirname + '/index.html');
});

const parser = port.pipe(new Readline({
    delimiter: "\r\n"
}));

parser.on("data", function (data) {
    console.log(data);
    io.sockets.emit('data', data);
});

io.on('connection', function (socket) {
    socket.on('data', function (msg) {
        console.log(msg.val);
        if (msg.val === "ping") {
            port.write('a\n')
        }
    });
});

io.on('error', function () {
    console.error(arguments)
});