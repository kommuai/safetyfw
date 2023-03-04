// ///////////////////////////////////////////////////////////// //
// Hardware abstraction layer for all different supported boards //
// ///////////////////////////////////////////////////////////// //
#include "boards/board_declarations.h"
#include "boards/unused_funcs.h"

// ///// Board definition and detection ///// //
#include "drivers/harness.h"
#include "drivers/fan.h"
#include "stm32h7/llfan.h"
#include "stm32h7/llrtc.h"
#include "stm32h7/lldac.h"
#include "drivers/fake_siren.h"
#include "drivers/rtc.h"
#include "drivers/clock_source.h"
#include "boards/red.h"
#include "boards/red_chiplet.h"
#include "boards/red_v2.h"
#include "boards/tres.h"

void detect_board_type(void) {

  hw_type = HW_TYPE_RED_PANDA;
  current_board = &board_red;
}
