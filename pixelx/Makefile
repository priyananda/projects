BIN_DIR=linux_bin
LIB_DIR=linux_lib
OBJ_DIR=linux_obj
COMMON_INCLUDES=-Isrc/Common/include
COMMON_OPTIONS=-std=c++14 -DPLATFORM_LINUX -Wall

all: prep $(BIN_DIR)/pixelx.so

$(BIN_DIR)/pixelx.so : $(LIB_DIR)/pxsound.a $(LIB_DIR)/pxinput.a $(LIB_DIR)/pxphysics.a $(LIB_DIR)/pxgraphics.a

PXINPUT_SRC_DIR=src/PxInput/src/Input
PXINPUT_OBJ_DIR=$(OBJ_DIR)/pxinput
PXINPUT_OBJS=$(PXINPUT_OBJ_DIR)/PxInputRoot.o $(PXINPUT_OBJ_DIR)/PxConfiguration.o
PXINPUT_INCLUDES=-Isrc/PxInput/include

$(LIB_DIR)/pxinput.a : $(PXINPUT_OBJS)
	ar r $@ $^

$(PXINPUT_OBJ_DIR)/%.o : $(PXINPUT_SRC_DIR)/%.cpp
	g++ -c $(COMMON_OPTIONS) $(COMMON_INCLUDES) $(PXINPUT_INCLUDES) -o $@ $<

PXSOUND_SRC_DIR=src/PxSound/src/Sound
PXSOUND_OBJ_DIR=$(OBJ_DIR)/pxsound
PXSOUND_OBJS=$(PXSOUND_OBJ_DIR)/PxAudioManager.o $(PXSOUND_OBJ_DIR)/PxSoundRoot.o
PXSOUND_INCLUDES=-Isrc/PxSound/include -Idep/

$(LIB_DIR)/pxsound.a : $(PXSOUND_OBJS)
	ar r $@ $^

$(PXSOUND_OBJ_DIR)/%.o : $(PXSOUND_SRC_DIR)/%.cpp
	g++ -c $(COMMON_OPTIONS) $(COMMON_INCLUDES) $(PXSOUND_INCLUDES) -o $@ $<

PXPHYSICS_SRC_DIR=src/PxPhysics/src/
PXPHYSICS_OBJ_DIR=$(OBJ_DIR)/pxphysics
PXPHYSICS_OBJS=\
	$(PXPHYSICS_OBJ_DIR)/PxBoundingSphere.o \
	$(PXPHYSICS_OBJ_DIR)/PxLine.o \
	$(PXPHYSICS_OBJ_DIR)/PxMath.o \
	$(PXPHYSICS_OBJ_DIR)/PxMatrix.o \
	$(PXPHYSICS_OBJ_DIR)/PxPhysicsRoot.o \
	$(PXPHYSICS_OBJ_DIR)/PxPlane.o \
	$(PXPHYSICS_OBJ_DIR)/PxPointProjectile.o \
	$(PXPHYSICS_OBJ_DIR)/PxProjectile.o \
	$(PXPHYSICS_OBJ_DIR)/PxVector4d.o \
	$(PXPHYSICS_OBJ_DIR)/PxVector.o \
	$(PXPHYSICS_OBJ_DIR)/PxCollisionManager.o \
	$(PXPHYSICS_OBJ_DIR)/PxNormalCollisionController.o \
	$(PXPHYSICS_OBJ_DIR)/PxQuakeCollisionController.o \

PXPHYSICS_INCLUDES=-Isrc/PxPhysics/include

$(LIB_DIR)/pxphysics.a : $(PXPHYSICS_OBJS)
	ar r $@ $^

$(PXPHYSICS_OBJ_DIR)/%.o : $(PXPHYSICS_SRC_DIR)/%.cpp
	g++ -c $(COMMON_OPTIONS) $(COMMON_INCLUDES) $(PXPHYSICS_INCLUDES) -o $@ $<

$(PXPHYSICS_OBJ_DIR)/%.o : $(PXPHYSICS_SRC_DIR)/Collision/%.cpp
	g++ -c $(COMMON_OPTIONS) $(COMMON_INCLUDES) $(PXPHYSICS_INCLUDES) -o $@ $<

PXGRAPHICS_SRC_DIR=src/PxGraphics/src/Graphics
PXGRAPHICS_OBJ_DIR=$(OBJ_DIR)/pxgraphics
PXGRAPHICS_INCLUDES=-Isrc/PxGraphics/include
PXGRAPHICS_OBJS= \
	$(PXGRAPHICS_OBJ_DIR)/PxBoundingBox.o \
	$(PXGRAPHICS_OBJ_DIR)/PxConsole.o \
	$(PXGRAPHICS_OBJ_DIR)/PxIndexedPolygonSet.o \
	$(PXGRAPHICS_OBJ_DIR)/PxPolygon.o \
	$(PXGRAPHICS_OBJ_DIR)/PxSimplePolygonSet.o \
	$(PXGRAPHICS_OBJ_DIR)/PxCamera.o \
	$(PXGRAPHICS_OBJ_DIR)/PxGraphicsRoot.o \
	$(PXGRAPHICS_OBJ_DIR)/PxLensFlare.o \
	$(PXGRAPHICS_OBJ_DIR)/PxRectangle.o \
	$(PXGRAPHICS_OBJ_DIR)/PxTextWriter.o \

$(LIB_DIR)/pxgraphics.a : $(PXGRAPHICS_OBJS)
	ar r $@ $^

$(PXGRAPHICS_OBJ_DIR)/%.o : $(PXGRAPHICS_SRC_DIR)/%.cpp
	g++ -c $(COMMON_OPTIONS) $(COMMON_INCLUDES) $(PXGRAPHICS_INCLUDES) -o $@ $<

prep:
	mkdir -p $(PXSOUND_OBJ_DIR) $(PXSOUND_OBJ_DIR) $(PXPHYSICS_OBJ_DIR) $(PXGRAPHICS_OBJ_DIR)

clean:
	rm -f $(PXINPUT_OBJ_DIR)/*
	rm -f $(PXSOUND_OBJ_DIR)/*
	rm -f $(PXPHYSICS_OBJ_DIR)/*
	rm -f $(PXGRAPHICS_OBJ_DIR)/*
	rm -f $(BIN_DIR)/*