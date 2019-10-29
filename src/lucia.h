//
//  lucia.h
//  lucia
//
//  Created by Luís Miguel Moreira Fonseca on 28/10/2019.
//  Copyright © 2019 Luís Miguel Moreira Fonseca. All rights reserved.
//

#ifndef lucia_h
#define lucia_h

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <chrono>

#include "scene.h"

#include "parser/factory.h"
#include "utility/image.h"
#include "utility/constants.h"
#include "tracer/tracer.h"
#include "tracer/naive.h"
#include "tracer/distributed.h"
#include "light/light.h"
#include "geometry/rectangle.h"
#include "geometry/grid.h"
#include "camera/lens.h"
#include "camera/pinhole.h"
#include "sampler/adaptive.h"
#include "sampler/regular.h"
#include "sampler/jittered.h"
#include "sampler/random.h"

#endif /* lucia_h */
