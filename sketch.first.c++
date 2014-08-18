#import "sketch.h"
#import "view.program.h"
#import "sym.h"

SKETCH { return _.spawn<program_v>("globe"); };
SKETCH { return _.spawn<program_v>("test");  };
SKETCH { return _.spawn<program_v>("mess");  };
SKETCH { return _;                           };
