#
# Copyright 2017 International Business Machines
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

#
# Generate HDL version of the HLS sources
#
# The generated HDL depends on the chip which is used and
# therefore must match what is being used to build the
# toplevel SNAP bitstream.
#
# FIXME Pass part_number and other parameters from toplevel
#      build-system as required.
#

# This is solution specific. Check if we can replace this by generics too.

# Finding $SNAP_ROOT
ifndef SNAP_ROOT
# check if we are in sw folder of an action (three directories below snap root)
ifneq ("$(wildcard ../../../ActionTypes.md)","")
SNAP_ROOT=$(abspath ../../../)
else
$(info You are not building your software from the default directory (/path/to/snap/actions/<action_name>/sw) or specified a wrong $$SNAP_ROOT.)
$(error Please make sure that $$SNAP_ROOT is set up correctly.)
endif
endif

include $(SNAP_ROOT)/snap_env.sh

ifdef NVDLA_ROOT

CXX     = $(CROSS)g++
CPPFLAGS += -I./nvdla-sw/umd/include \
	    -I./nvdla-sw/umd/tests/runtime \
	    -I./nvdla-sw/umd/core/include \
	    -DNVDLA_UTILS_ERROR_TAG="\"DLA_TEST\""

all: config all_build 

config:
	./action_config.sh

SUBDIRS_UMD = nvdla-sw/umd/core/runtime \
	  nvdla-sw/umd/tests/runtime
SUBDIRS_KMD = nvdla-sw/kmd/firmware \
	  nvdla-sw/kmd/port/capi
NVDLA_UMD_OUT = nvdla-sw/umd/out/runtime/
NVDLA_KMD_OUT = nvdla-sw/umd/out/

projs += snap_nvdla

nvdla_capi_test.o Runtime.o Emulator.o Check.o:
	for dir in $(SUBDIRS_UMD); do \
		$(MAKE) -C $$dir; \
	done
	cp -f $(NVDLA_UMD_OUT)/nvdla_runtime/*.o $(ACTION_ROOT)/sw/
	cp -f $(NVDLA_UMD_OUT)/libnvdla_runtime/*.o $(ACTION_ROOT)/sw/
	cp -f $(NVDLA_UMD_OUT)/libnvdla_runtime/$(ACTION_ROOT)/sw/nvdla-sw/umd/core/common/*.o $(ACTION_ROOT)/sw/
	cp -f $(NVDLA_UMD_OUT)/libnvdla_runtime/$(ACTION_ROOT)/sw/nvdla-sw/umd/port/linux/*.o $(ACTION_ROOT)/sw/

snap_nvdla_umd_objs += nvdla_capi_test.o \
		   Server.o \
		   DlaImageUtils.o \
		   DlaImage.o \
		   TestUtils.o \
		   RuntimeTest.o \
		   Runtime.o \
		   Emulator.o \
		   Check.o \
		   Loadable.o \
		   ErrorLogging.o \
		   EMUInterfaceA.o \
		   EMUInterface.o \
		   nvdla.o \
		   nvdla_os.o

nvdla_capi.o nvdla_core_callbacks.o:
	for dir in $(SUBDIRS_KMD); do \
		$(MAKE) -C $$dir; \
	done
	cp -f $(NVDLA_KMD_OUT)/kmd/libnvdla_kmd/*.o $(ACTION_ROOT)/sw/
	cp -f $(NVDLA_KMD_OUT)/firmware/libnvdla_firmware/*.o $(ACTION_ROOT)/sw/

snap_nvdla_kmd_objs += nvdla_capi.o \
		   nvdla_core_callbacks.o \
                   scheduler.o \
                   engine.o \
                   bdma.o \
                   conv.o \
                   sdp.o \
                   cdp.o \
                   pdp.o \
                   rubik.o \
                   cache.o \
                   common.o \
                   engine_data.o \
                   engine_isr.o \
                   engine_debug.o

snap_nvdla: $(snap_nvdla_umd_objs) $(snap_nvdla_kmd_objs)

projs += snap_nvdla

snap_nvdla: snap_nvdla.o $(snap_nvdla_umd_objs) $(snap_nvdla_kmd_objs)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $($(@)_LDFLAGS) $@.o $($(@)_objs) $($(@)_umd_objs) $($(@)_kmd_objs) $($(@)_libs) $(LDLIBS) -lrt -ljpeg -o $@

else
$(info NVDLA_ROOT is not set, no sw will be built for hdl_nvdla.)
endif

# If you have the host code outside of the default snap directory structure, 
# change to /path/to/snap/actions/software.mk
include $(SNAP_ROOT)/actions/software.mk