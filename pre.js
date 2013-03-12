var Module = {
  initialize: function() {Module._init();},

  step: function() {Module._step();},
  //flda: new Float32Array(5),

  get_num_points: function() {Module.ccall('get_num_points', 'number', null, [])},

  get_points: function() {
    var ptr = Module.ccall('get_points', null, null, []);
    var n   = Module.ccall('get_num_points', 'number', null, []);

    // https://groups.google.com/forum/?fromgroups=#!topic/emscripten-discuss/oeEg6WrZ7rg
    //new UInt8Array(Module.HEAPU8.buffer, ptr, n*Module.flda.BYTES_PER_ELEMENT)
    var floatData = []
    for (var i = 0; i < n; i++) {
      floatData[i] = {x: Module.getValue(ptr+(i*3+0)*4, 'float'),
                      y: Module.getValue(ptr+(i*3+1)*4, 'float'),
                      z: Module.getValue(ptr+(i*3+2)*4, 'float')};
    }
    return floatData;
  },
};
