#include <stdbool.h>
#include <stdio.h>

#include "common/cs_dbg.h"

#include "fw/src/mgos_app.h"


extern bool mgos_blynk_init(void);
extern bool mgos_ca_bundle_init(void);
extern bool mgos_wifi_init(void);
extern bool mgos_http_server_init(void);
extern bool mgos_mjs_init(void);
extern bool mgos_mqtt_init(void);
extern bool mgos_ota_http_client_init(void);
extern bool mgos_pwm_init(void);
extern bool mgos_rpc_common_init(void);
extern bool mgos_rpc_service_config_init(void);
extern bool mgos_rpc_service_fs_init(void);
extern bool mgos_rpc_service_ota_init(void);
extern bool mgos_rpc_uart_init(void);

static const struct lib_descr {
  const char *title;
  bool (*init)(void);
} descrs[] = {

  // "blynk". deps: [ ]
  {
    .title = "blynk",
    .init = mgos_blynk_init,
  },

  // "ca_bundle". deps: [ ]
  {
    .title = "ca_bundle",
    .init = mgos_ca_bundle_init,
  },

  // "wifi". deps: [ ]
  {
    .title = "wifi",
    .init = mgos_wifi_init,
  },

  // "http_server". deps: [ "atca" "ethernet" "wifi" ]
  {
    .title = "http_server",
    .init = mgos_http_server_init,
  },

  // "mjs". deps: [ ]
  {
    .title = "mjs",
    .init = mgos_mjs_init,
  },

  // "mqtt". deps: [ ]
  {
    .title = "mqtt",
    .init = mgos_mqtt_init,
  },

  // "ota_http_client". deps: [ ]
  {
    .title = "ota_http_client",
    .init = mgos_ota_http_client_init,
  },

  // "pwm". deps: [ ]
  {
    .title = "pwm",
    .init = mgos_pwm_init,
  },

  // "rpc_common". deps: [ "http-server" ]
  {
    .title = "rpc_common",
    .init = mgos_rpc_common_init,
  },

  // "rpc_service_config". deps: [ "rpc-common" ]
  {
    .title = "rpc_service_config",
    .init = mgos_rpc_service_config_init,
  },

  // "rpc_service_fs". deps: [ "rpc-common" ]
  {
    .title = "rpc_service_fs",
    .init = mgos_rpc_service_fs_init,
  },

  // "rpc_service_ota". deps: [ "ota-http-client" "rpc-common" ]
  {
    .title = "rpc_service_ota",
    .init = mgos_rpc_service_ota_init,
  },

  // "rpc_uart". deps: [ "rpc-common" ]
  {
    .title = "rpc_uart",
    .init = mgos_rpc_uart_init,
  },

};

bool mgos_deps_init(void) {
  size_t i;
  for (i = 0; i < sizeof(descrs) / sizeof(struct lib_descr); i++) {
    LOG(LL_DEBUG, ("init %s...", descrs[i].title));
    if (!descrs[i].init()) {
      LOG(LL_ERROR, ("%s init failed", descrs[i].title));
      return false;
    }
  }

  return true;
}
