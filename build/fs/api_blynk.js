let Blynk = {
  _send: ffi('void blynk_send(void *, int, int, void *, int)'),

  // **`Blynk.send(conn, type, msg)`**
  // Send raw message to Blynk server. If id is undefined, it will be
  // autogenerated.
  send: function(conn, type, msg, id) {
    this._send(conn, type, id || 0, msg, msg.length);
  },

  // **`Blynk.virtualWrite(conn, pin, val)`**
  // Write to the virtual pin. If id is undefined, it will be autogenerated.
  // This is a helper function that uses `Blynk.send()`
  virtualWrite: function(conn, pin, val, id) {
    let msg = 'vw\x00' + JSON.stringify(pin) + '\x00' + JSON.stringify(val);
    this.send(conn, 20, msg, id);
  },

  // **`Blynk.setHandler(handler)`**
  // Set handler for the virtual pin reads / writes.
  // 
  // Example:
  // ```javascript
  // Blynk.setHandler(function(conn, cmd, pin, val, id) {
  //   print(cmd, pin, val);
  // }, null);
  // ```
  setHandler: ffi('void blynk_set_handler(void (*)(void *, char *, int, int, int, userdata), userdata)'),
};
