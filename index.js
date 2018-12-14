//index.js
const addon = require('./build/Release/testaddon.node');

const classInstance = new addon.ClassExample(4.3);

//console.log('addon',addon);
//console.log('hello() => ',addon.hello());
//console.log('add()   => ', addon.add(23,45));

//console.log('Testing class initial value : ',classInstance.getValue());
//console.log('After adding 3.3 : ',classInstance.add(3.3));

//console.log('addCallback()   => ', addon.addCallback(2,4, (err, result) => console.log(`callback ${result} yay`) ));

var log = () => console.log("SUCCEESSSSSSS");

classInstance.setFunction(log);

classInstance.callFunction();
classInstance.init();
//classInstance.start();

module.exports = addon;
