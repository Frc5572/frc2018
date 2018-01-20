"use strict";

var drive = require('./drive');

var http = require('http'),
    https = require("https"),
    url = require('url'),
    fs = require('fs'),
    path = require('path'),
    qs = require('querystring'),
    request = require('request'),
    waitUntil = require('wait-until');

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

var current_tba = {hasdata : false, data: {}, current_match: 0};

var current_team = 0;

function tba(ev){
  fs.readFile('tba.json', function(err, data) {
    var options = {
      url: 'https://www.thebluealliance.com/api/v3/event/' + ev + '/matches/simple',
      headers: {
	'X-TBA-Auth-Key' : data.toString()
      }
    };
    request(options, function (error, response, body) {
      if (!error && response.statusCode == 200) {
	current_tba.data = JSON.parse(body).filter(function(element) {
	  return element.comp_level == 'qm';
	}).sort(function(a, b){
	  return a.match_number > b.match_number ? 1 : (a.match_number < b.match_number ? -1 : 0);
	});
	current_tba.hasdata = true;
      }
    });
  });
}

function event(ev){
  drive.setEvent(ev, function(existed){
    tba(ev);
    drive.lastMatch(function(d){
      if(typeof d.values != 'undefined')
      for(let i = 1; i < d.values.length; i++){
	var matchi = parseInt(d.values[i][0]);
	if(current_tba.current_match <= matchi){
	  current_tba.current_match = matchi;
	}
      }
    });
  });
}

drive(function(){
  if(drive.hasEvent()){
    tba(drive.getEventName());
    drive.lastMatch(function(d){
      if(typeof d.values != 'undefined')
      for(let i = 1; i < d.values.length; i++){
	var matchi = parseInt(d.values[i][0]);
	if(current_tba.current_match <= matchi){
	  current_tba.current_match = matchi;
	}
      }
    });
  } else {
    console.log("no event");
  }
});

var authcode = '';
var awaiting_auth = false;

http.createServer(function (req, res) {
  if (req.method == 'POST') {
    var ended = false;
    var body = '';
    req.on('data', function (data) {
      body += data;
    });
    req.on('end', function () {
      var post = qs.parse(body);
      if(req.url == '/submit'){
	current_tba.current_match = parseInt(post['Match Number']);
	current_team = 0;
	drive.submit(post, function(){
	  console.log("Submitted");
	});
	
      } else if(req.url == '/event'){
	
      }
      ended = true;
    });
    waitUntil()
    .interval(50)
    .times(1000)
    .condition(function(cb) {
      process.nextTick(function() {
        cb(ended);
      });
    })
    .done(function(result) {
      fs.readFile('submitted.html', function(err, data) {
	res.writeHead(200, {'Content-Type': 'text/html'});
	res.write(data);
	res.end();
      });
    });
    return;
  }
  if(req.url == "/favicon.ico"){
    res.end();
    return;
  }
  if(req.url == "/new"){
    drive.authSetup(function(){
      res.writeHead(200, {'Content-Type': 'text/html'});
      res.write('Change Meta file, then use auth code');
      res.end();
      awaiting_auth = true;
    });
    return;
  }
  if(req.url == "/" + authcode && awaiting_auth){
    console.log("Changing Event");
    drive.authUse(function(v, d){
      if(!v){
        res.writeHead(200, {'Content-Type': 'text/html'});
        res.write('Incorrect Code');
        res.end();
        return;
      }
      event(d);
      res.writeHead(200, {'Content-Type': 'text/html'});
      res.write('Event changed');
      res.end();
      awaiting_auth = false;
    });
    return;
  }
  if(!current_tba.hasdata || typeof current_tba.data == 'undefined' || typeof current_tba.data[current_tba.current_match] == 'undefined' || typeof current_tba.data[current_tba.current_match].alliances == 'undefined'){
    res.writeHead(200, {'Content-Type': 'text/html'});
    res.write('No Event');
    res.end();
    return;
  }
  fs.readFile('form.html', function(err, data) {
    var alliance = current_team > 2 ?  current_tba.data[current_tba.current_match].alliances.blue : current_tba.data[current_tba.current_match].alliances.red;
    if(current_team < 6) {
      var team = alliance.team_keys[current_team % 3].substr(3);
    } else {
      var team = 0;
      data = data.toString().replace('<!--MSG-->', 'All teams are being scored. If you need to take over, you must insert the team number below');
    }
    current_team++;
    res.writeHead(200, {'Content-Type': 'text/html'});
    res.write(data.toString().replace('$team', team).replace('$matchno', current_tba.current_match + 1));
    res.end();
  });
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
