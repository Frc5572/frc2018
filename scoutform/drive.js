"use strict";

const order_vals = {
  get : 1,
  meta_get : 2,
  meta_set : 3,
  update : 4,
  append : 5,
  drive_list : 6,
  drive_new : 7
};

const meta_file_name = 'Meta';
const folder_name = 'Scouting-Files';

var current_event = "";
var eventname = "";

var gauth = require('./gsheet');
var readline = require('readline');
var waitUntil = require('wait-until');
var google = require('googleapis');

var drive = google.drive('v3');
var sheets = google.sheets('v4');

var ready = false;

var Meta = "";
var ServerFolder = "";

function nauth(authUrl, callback){
  console.log('Authorize this app by visiting this url: ', authUrl);
  var rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
  });
  rl.question('Enter the code from that page here: ', function(code) {
    rl.close();
    callback(code);
  });
}

function isFunction(functionToCheck) {
  var getType = {};
  return functionToCheck && getType.toString.call(functionToCheck) === '[object Function]';
}

function pass_Function(auth, map, args){
  for(let i = 0; i < map.functions.length; i++){
    args[map.functions[i]]();
  }
}

function make_Append(sheet, range, values, cb){
  return {
    reqtype : 'append',
    spreadsheet : sheet,
    cb : cb,
    req : {
      range : range,
      data : values
    }
  };
}

function pass_Append(auth, map, args){
  var spreadsheets = {};
  var sscb = {};
  for(var i = 0; i < map.append.length; i++){
    var req = args[map.append[i]];
    spreadsheets[req.spreadsheet] = spreadsheets[req.spreadsheet] || [];
    spreadsheets[req.spreadsheet].push(req.req);
    sscb[req.spreadsheet] = sscb[req.spreadsheet] || [];
    sscb[req.spreadsheet].push(req.cb);
  }
  for (var key in spreadsheets) {
    if (spreadsheets.hasOwnProperty(key)) {
      for(let i = 0; i < spreadsheets[key].length; i++){
	sheets.spreadsheets.values.append({
	  spreadsheetId : key,
	  range : spreadsheets[key][i].range,
	  valueInputOption : 'USER_ENTERED',
	  resource : {
	    values : spreadsheets[key][i].data
	  },
	  auth : auth
	}, function(err, result) {
	  if(err) {
	    console.log(err);
	    gauth.reset_auth();
	  } else {
	    sscb[key][i](result);
	  }
	});
      }
    }
  }
  pass(auth, map, args);
}

function make_Update(sheet, range, values, cb){
  return {
    reqtype : 'update',
    spreadsheet : sheet,
    cb : cb,
    req : {
      range : range,
      values : values
    }
  };
}

function pass_Update(auth, map, args){
  var spreadsheets = {};
  var sscb = {};
  for(var i = 0; i < map.update.length; i++){
    var req = args[map.update[i]];
    spreadsheets[req.spreadsheet] = spreadsheets[req.spreadsheet] || [];
    spreadsheets[req.spreadsheet].push(req.req);
    sscb[req.spreadsheet] = sscb[req.spreadsheet] || [];
    sscb[req.spreadsheet].push(req.cb);
  }
  for (let key in spreadsheets) {
    if (spreadsheets.hasOwnProperty(key)) {
      var body = {
	spreadsheetId: key,
	resource: {
	  valueInputOption : 'USER_ENTERED',
	  data : spreadsheets[key]
	},
	auth : auth
      };
      sheets.spreadsheets.values.batchUpdate(body, function(err, result) {
	if(err) {
	  console.log(err);
	  gauth.reset_auth();
	} else {
	  for(var i = 0; i < sscb[key].length; i++)
	  sscb[key][i](result);
	}
      });
    }
  }
  pass(auth, map, args);
}

function pass_MetaGet(auth, map, args){ // TODO
  var spreadsheets = {};
  var sscb = {};
  for(var i = 0; i < map.meta_get.length; i++){
    var req = args[map.meta_get[i]];
    spreadsheets[req.spreadsheet] = spreadsheets[req.spreadsheet] || [];
    spreadsheets[req.spreadsheet].push(req.req);
    sscb[req.spreadsheet] = sscb[req.spreadsheet] || [];
    sscb[req.spreadsheet].push(req.cb);
  }
  for (let key in spreadsheets) {
    if (spreadsheets.hasOwnProperty(key)) {
      sheets.spreadsheets.get({
	spreadsheetId : key,
	ranges: spreadsheets[key].ranges || [],
	includeGridData: spreadsheets[key].grid || false,
	auth : auth
      },function(err, response) {
	if (err) {
	  console.error(err);
	  gauth.reset_auth();
	  return;
	}
	for(var i = 0; i < sscb[key].length; i++)
	  sscb[key][i](response);
      });
    }
  }
  pass(auth, map, args);
}

function pass_MetaSet(auth, map, args){
  var spreadsheets = {};
  var sscb = {};
  for(var i = 0; i < map.meta_set.length; i++){
    var req = args[map.meta_set[i]];
    spreadsheets[req.spreadsheet] = spreadsheets[req.spreadsheet] || [];
    spreadsheets[req.spreadsheet].push(req.req);
    sscb[req.spreadsheet] = sscb[req.spreadsheet] || [];
    sscb[req.spreadsheet].push(req.cb);
  }
  for (let key in spreadsheets) {
    if (spreadsheets.hasOwnProperty(key)) {
      sheets.spreadsheets.batchUpdate({
	spreadsheetId : key,
	resource: {
	  requests: spreadsheets[key]
	},
	auth : auth
      },function(err, response) {
	if (err) {
	  console.error(err);
	  gauth.reset_auth();
	  return;
	}
	if(sscb)
	for(var i = 0; i < sscb[key].length; i++)
	  if(sscb[key] && sscb[key][i] && isFunction(sscb[key][i]))
	    sscb[key][i](response.replies[i]);
      });
    }
  }
  pass(auth, map, args);
}

function make_AddSheet(sheet, title, row, col, r, g, b, id, cb){
  return id ? {
    reqtype: 'meta_set',
    spreadsheet : sheet,
    cb : cb,
    req: {
      addSheet: {
	properties: {
	  sheetId : id,
	  title: title,
	  gridProperties: {
	    rowCount: row,
	    columnCount: col
	  },
	  tabColor: {
	    red: r,
	    green: g,
	    blue: b
	  }
	}
      }
    }
  } : {
    reqtype: 'meta_set',
    spreadsheet : sheet,
    cb : cb,
    req: {
      addSheet: {
	properties: {
	  title: title,
	  gridProperties: {
	    rowCount: row,
	    columnCount: col
	  },
	  tabColor: {
	    red: r,
	    green: g,
	    blue: b
	  }
	}
      }
    }
  };
}

function make_DelSheet(sheet, sheetId, cb){
  return {
    reqtype: 'meta_set',
    spreadsheet : sheet,
    cb : cb,
    req: {
      deleteSheet: {
	sheetId : sheetId
      }
    }
  };
}

function pass_DriveList(auth, map, args){
  drive.files.list({
    auth: auth,
    pageSize: 10,
    fields: "nextPageToken, files(id, name)"
  }, function(err, response) {
    if (err) {
      console.log('The API returned an error: ' + err);
      gauth.reset_auth();
      return;
    }
    for(var i = 0; i < map.drive_list.length; i++){
      args[map.drive_list[i]].cb(response);
    }
    pass(auth, map, args);
  });
}

function drivecreatehelper(auth, data, cbs, finalcallback){
  drive.files.create({
    resource: data[0],
    fields: 'id',
    auth: auth
  }, function (err, file) {
    if (err) {
      // Handle error
      console.error(err);
      gauth.reset_auth();
    } else {
      if(cbs.length > 1){
	cbs.shift()(file);
	data.shift();
	drivecreatehelper(auth, data, cbs, finalcallback);
      } else {
	cbs.shift()(file);
	finalcallback();
      }
    }
  });
}

function pass_DriveCreate(auth, map, args){
  var data = [];
  var cbs = [];
  for(let i = 0; i < map.drive_new.length; i++){
    data.push(args[map.drive_new[i]].meta);
    cbs.push(args[map.drive_new[i]].cb);
  }
  drivecreatehelper(auth, data, cbs, function(){
    pass(auth, map, args);
  });
}

function make_DriveCreate(name, mimeType, parents, cb){
  return {
    reqtype : 'drive_new',
    meta : {
      name : name,
      mimeType : mimeType,
      parents : parents || []
    },
    cb : cb || function(){}
  }
}

function make_Get(sheet, range, cb){
  return {
    reqtype : 'get',
    spreadsheet : sheet,
    range : range,
    cb : cb
  };
}

function pass_Get(auth, map, args){
  var spreadsheets = {};
  var sscb = {};
  for(var i = 0; i < map.get.length; i++){
    var req = args[map.get[i]];
    spreadsheets[req.spreadsheet] = spreadsheets[req.spreadsheet] || [];
    spreadsheets[req.spreadsheet].push(req.range);
    sscb[req.spreadsheet] = sscb[req.spreadsheet] || [];
    sscb[req.spreadsheet].push(req.cb);
  }
  for (let key in spreadsheets) {
    if (spreadsheets.hasOwnProperty(key)) {
      sheets.spreadsheets.values.batchGet({
	spreadsheetId: key,
	ranges: spreadsheets[key],
	auth: auth
      }, function(err, result) {
	if(err) {
	  // Handle error
	  console.log(err);
	  gauth.reset_auth();
	} else {
	  for(var i = 0; i < sscb[key].length; i++){
	    var data = result.valueRanges[i];
	    data.spreadsheetId = key;
	    sscb[key][i](data);
	  }
	}
      });
    }
  }
  pass(auth, map, args);
}

function pass(auth, map, args){
  if(map.order.length > 0){
    var nextpass = map.order.shift();
    switch(nextpass) {
      case order_vals.get : 
	pass_Get(auth, map, args);
	return;
      case order_vals.drive_list : 
	pass_DriveList(auth, map, args);
	return;
      case order_vals.drive_new : 
	pass_DriveCreate(auth, map, args);
	return;
      case order_vals.meta_get : 
	pass_MetaGet(auth, map, args);
	return;
      case order_vals.meta_set : 
	pass_MetaSet(auth, map, args);
	return;
      case order_vals.update : 
	pass_Update(auth, map, args);
	return;
      case order_vals.append : 
	pass_Append(auth, map, args);
	return;
    }
  } else {
    if(map.functions && map.functions.length > 0)
      pass_Function(auth, map, args);
  }
}

function dostuff(require_wait, dargs){
  if(dargs.length == 0) return;
  let map = {order: []}
  let forefuncs = [];
  var fore = true;
  let args = [];
  for (var i = 0; i < dargs.length; i++) {
    args.push(dargs[i]);
    if(isFunction(dargs[i])){
      if(fore){
	forefuncs.push(i);
      } else {
	map.functions = map.functions || [];
	map.functions.push(i);
      }
    } else if(dargs[i].reqtype) {
      fore = false;
      if(!map[dargs[i].reqtype]){
	map[dargs[i].reqtype] = [];
	if(order_vals[dargs[i].reqtype])
	  map.order.push(order_vals[dargs[i].reqtype]);
	else
	  console.log("unknown type", dargs[i].reqtype);
      }
      map[dargs[i].reqtype].push(i);
    }
  }
  if(require_wait){
    waitUntil()
    .interval(50)
    .times(1000)
    .condition(function(cb) {
      process.nextTick(function() {
        cb(ready);
      });
    })
    .done(function(result) {
      gauth.authenticate(function(auth){
	if(forefuncs.length > 0){
	  for(var i = 0; i < forefuncs.length; i++){
	    args[forefuncs[i]]();
	  }
	}
	pass(auth, map, args);
      }, nauth);
    });
  } else {
    gauth.authenticate(function(auth){
	if(forefuncs.length > 0){
	  for(var i = 0; i < forefuncs.length; i++){
	    args[forefuncs[i]]();
	  }
	}
	pass(auth, map, args);
      }, nauth);
  }
}

module.exports = function(){
  dostuff(true, arguments);
}

module.exports.asList = function(v){
  dostuff(true, v);
}

module.exports.hasEvent = function(){
  return current_event != "";
}

module.exports.getEventName = function(){
    return eventname;
}

module.exports.lastMatch = function(rcb){
  dostuff(true, [function(){
    dostuff(true, [make_Get(current_event,'Data!B1:B',function(data){
      rcb(data);
    })]);
  }]);
}

module.exports.submit = function(data, rcb){
  dostuff(true, [function(){
    var values = [[]];
    for (var key in data) {
      if (data.hasOwnProperty(key)) {
	values[0].push(key);
      }
    }
    dostuff(true, [make_Update(current_event, 'Data!A1:' + String.fromCharCode('A'.charCodeAt(0) + values[0].length) + '1', values, function(){
      values[0] = [];
      for (var key in data) {
	if (data.hasOwnProperty(key)) {
	  values[0].push(data[key]);
	}
      }
      dostuff(true, [make_Append(current_event, 'Data!A1', values, function(){
	rcb();
      })]); // sheet, range, values, cb
    })]);
  }]);
}

module.exports.setEvent = function(name, rcb){
  dostuff(true, [function(){
    dostuff(true, [make_Update(Meta, 'Sheet1!A1', [[name]], function(){
      dostuff(true, [{reqtype: 'drive_list', cb : function(response){
	var files = response.files;
	for(let i = 0; i < files.length; i++){
	  if(files[i].name == name){
	    current_event = files[i].id;
	    eventname = name;
	    rcb(true);
	    return;
	  }
	}
	dostuff(true, [make_DriveCreate(name, 'application/vnd.google-apps.spreadsheet', [ServerFolder], function(sheet){
	  current_event = sheet.id;
	  eventname = name;
	  dostuff(true, [make_AddSheet(current_event, 'Data', 1, 1, 0.0, 1.0, 0.0, 11000, function(matchSheet){
	    dostuff(true, [make_AddSheet(current_event, 'meta', 1, 1, 0.0, 1.0, 1.0, 11002, function(matchSheet){
	      rcb(false);
	    })]);
	  }), {reqtype : 'meta_get', spreadsheet : current_event, req : {ranges : ['Sheet1']}, cb : function(response){
	    dostuff(true, [make_DelSheet(current_event, response.sheets[0].sheetId, function(){})]);
	  }}]);
	  return;
	})]);
      }}]);
    })]);
  }]);
}

/** Startup */
gauth.authenticate(function(auth){
  console.log("Starting Up Google Integration");
  dostuff(false, [{reqtype: 'drive_list', cb : function(response){
    var files = response.files;
    var num = 0;
    for(let i = 0; i < files.length; i++){
      if(files[i].name == meta_file_name && Meta == ""){
	Meta = files[i].id;
	num++;
      } else if (files[i].name == folder_name && ServerFolder == "") {
	ServerFolder = files[i].id;
	num++
      }
    }
    if(num < 2){
      dostuff(false, [make_DriveCreate(folder_name, 'application/vnd.google-apps.folder', [], function(data){
	ServerFolder = data.id;
	dostuff(false, [make_DriveCreate(meta_file_name, 'application/vnd.google-apps.spreadsheet', [data.id], function(sheet){
	  Meta = sheet.id;
	  dostuff(false, [make_AddSheet(sheet.id, "Auth", 1, 1, 1.0, 0.0, 0.0, function (response) {
	    ready = true;
	  })]);
	})]);
      })]);
    } else {
      dostuff(false, [make_Get(Meta, 'Sheet1!A1', function(response){
	if(response.values){
	  var last_file = response.values[0][0];
	  dostuff(false, [{reqtype: 'drive_list', cb : function(list){
	    var files = list.files;
	    for(let i = 0; i < files.length; i++){
	      if(files[i].name == last_file){
		console.log("Resuming event " + last_file);
		current_event = files[i].id;
		eventname = last_file;
		ready = true;
		return;
	      }
	    }
	    console.log("Records claim last event was " + last_file + " but no such event file was found...");
	    ready = true;
	  }
	}]);} else {
	  ready = true;
	}
      })]);
    }
  }}]);
}, nauth);