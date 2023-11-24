//
// Mock implementation for Node.js
//

Module.preRun = [
  function () 
  {
    FS.mkdir('/test');
    FS.mount(NODEFS, { root: '../../../Test/test' }, '/test');

    FS.mkdir('/resources');
    FS.mount(NODEFS, { root: '../../App/resources' }, '/resources');

    //
    // Mock Implementations 
    //
    global.navigator = {
      getGamepads() { return []; }
    };

    global.window = {
      alert(text) { console.error(text); },
      addEventListener() {},
      removeEventListener() {},
      speechSynthesis: {
        getVoices() { return []; }
      },
      screen: {}
    };

    global.document = {
      createElement() { 
        return { 
          style: {},
          addEventListener() {},
          removeEventListener() {},
        };
      }, 
    };
    
    Module.canvas = {
      style: {
        removeProperty() {}
      },
      parentNode: {
        prepend() {}
      },
      addEventListener() {},
      removeEventListener() {},
    };

    global.FileReader = class {
      constructor() {}
    };

    global.Notification = {
      permission: "granted",
      requestPermission() {}
    };

    global.XMLHttpRequest = require("xmlhttprequest").XMLHttpRequest;

    global.requestAnimationFrame = function(callback) {
      setTimeout(callback, 16);
    };
  }
];
