"use strict";

var drive = require('./drive');

var http = require('http'),
    url = require('url'),
    fs = require('fs'),
    path = require('path');

/*
drive(function(){
  drive.authenticate("admin", "admin", function(id){
    console.log(id);
  }, function(){
    console.log("failed to login");
  });
});
*/

function restartServer(){
  process.exit(200);
}

function event(ev){
  drive.setEvent(ev, function(existed){});
}

http.createServer(function (req, res) {
  console.log(req.url);
  res.writeHead(200, {'Content-Type': 'text/html'});
  res.write("<head><title>Form Title</title></head>");
  res.end();
}).listen(8080);
/*
var gamedata = {variables : 0};

function afterSetup(){
  console.log("Drive: afterSetup()");
  drive.listMatches(gamedata, function(response){
    console.log(response.values.length);
    
  });
}

drive(function(){
  console.log("Drive: Setup Complete");
  if(drive.hasEvent()){
    console.log("hasEvent");
    afterSetup();
    return;
  }
  drive.event("testEvent", gamedata, function(newid, existed){
    console.log("Drive: Created testEvent");
    if(!existed){
      var teams = JSON.parse(scout.tba("event/2017txsa/teams/simple"));
      var matches = JSON.parse(scout.tba("event/2017txsa/matches/simple"));
      drive.tbaSetUp(matches, teams, gamedata, function(result){
      console.log("Drive: Set up TBA");
	afterSetup();
      });
    } else {
      afterSetup();
    }
  });
});

*/