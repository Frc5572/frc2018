var http = require('http'),
    url = require('url'),
    fs = require('fs'),
    path = require('path'),
    mapper = require('./mapper');

http.createServer(function (req, res) {
  if(req.url == "/traverse"){ // Get robot path data
    
    return;
  }
  fs.readFile('page.html', function(err, data) {
    res.writeHead(200, {'Content-Type': 'text/html'});
    res.write(data.toString().replace("<!--MAP-->", "<rect x='20' y='20' width='360' height='323.38' style='stroke:rgb(0,0,0);stroke-width:5;fill:rgb(0,128,0);fill-opacity:0.3;'></rect><line x1='20' y1='49.69' x2='55' y2='20' style='stroke:rgb(0,0,0);stroke-width:5;'></line><line x1='20' y1='313.69' x2='55' y2='343.38' style='stroke:rgb(0,0,0);stroke-width:5;'></line>"));
    res.end();
  });
}).listen(8080);
