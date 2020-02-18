#define main SDL_main
#include <Ole2.h>
#include <Windows.h>
#include <SDL_opengl.h>
#include <SDL.h>
#include <Kinect.h>
#include <stdio.h>
#include <set>  // заголовочный файл множеств и мультимножеств
#include <iterator>
#include <cstdlib>
#include <iostream>

#define width 512
#define height 424

#undef main


// OpenGL Variables
GLuint textureId;              // ID of the texture to contain Kinect RGB Data
GLubyte data[width * height * 4];  // BGRA array containing the texture data

// Kinect variables
IKinectSensor* sensor;         // Kinect sensor
IColorFrameReader* reader;		// Kinect color data source
IDepthFrameReader* reader_depth;

UINT16 buf_depth[width * height];

int count = 0;

bool init(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface* screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL);
	return screen;
}

bool initKinect() {
	if (FAILED(GetDefaultKinectSensor(&sensor))) {
		return false;
	}
	if (sensor) {
		sensor->Open();
		IColorFrameSource* framesource = NULL;
		sensor->get_ColorFrameSource(&framesource);
		framesource->OpenReader(&reader);
		if (framesource) {
			framesource->Release();
			framesource = NULL;
		}
		return true;
	}
	else {
		return false;
	}
}

bool initKinectDepth() {
	if (FAILED(GetDefaultKinectSensor(&sensor))) {
		return false;
	}
	if (sensor) {
		sensor->Open();
		IDepthFrameSource* framesource = NULL;
		sensor->get_DepthFrameSource(&framesource);
		framesource->OpenReader(&reader_depth);
		if (framesource) {
			framesource->Release();
			framesource = NULL;
		}
		return true;
	}
	else {
		return false;
	}
}

int LU_count(int count) {
	if (((count - (width)-1) < 0) || ((count - (width)-1) > 217087)) {
		return 0;
	}
	return count - (width + 1);
}

int MU_count(int count) {
	if (((count - (width)) < 0) || ((count - (width)) > 217087)) {
		return 0;
	}
	return count - (width);
}

int RU_count(int count) {
	if (((count - (width)+1) < 0) || ((count - (width)+1) > 217087)) {
		return 0;
	}
	return count - (width) + 1;
}

int LC_count(int count) {
	if (((count - 1) < 0) || ((count - 1) > 217087)) {
		return 0;
	}
	return count - 1;
}

int RC_count(int count) {
	if (((count +  1) < 0) || ((count + 1) > 217087)) {
		return 0;
	}
	return count + 1;
}

int LD_count(int count) {
	if (((count + (width - 1)) < 0) || ((count + (width - 1)) > 217087)) {
		return 0;
	}
	return count + (width - 1);
}

int MD_count(int count) {
	if (((count + (width)) < 0) || ((count + (width)) > 217087)) {
		return 0;
	}
	return count + (width);
}

int RD_count(int count) {
	if (((count + (width + 1)) < 0) || ((count + (width + 1)) > 217087)) {
		return 0;
	}
	return count + (width) + 1;
}

void check_for_local(int number, UINT16* buf, std::set<int> *Set1) {
	(*Set1).insert(number);
	count++;
	printf("%d\n", count);
	int delta = 10;
	if ((*(buf + LU_count(number)) >= 1000) && (*(buf + LU_count(number)) <= 2000) &&
		(((*(buf + LU_count(number)) - *(buf + number)) <= delta) && (((*(buf + number)) - (*(buf + LU_count(number)))) <= delta)) &&
		((*Set1).count(LU_count(number)) != 1)) {
		check_for_local(LU_count(number), buf, Set1);

	}

	if ((*(buf + MU_count(number)) >= 1000) && (*(buf + MU_count(number)) <= 2000) &&
		(((*(buf + MU_count(number)) - *(buf + number)) <= delta) && (((*(buf + number)) - (*(buf + MU_count(number)))) <= delta)) &&
		((*Set1).count(MU_count(number)) != 1)) {
		check_for_local(MU_count(number), buf, Set1);

	}

	if ((*(buf + RU_count(number)) >= 1000) && (*(buf + RU_count(number)) <= 2000) &&
		(((*(buf + RU_count(number)) - *(buf + number)) <= delta) && (((*(buf + number)) - (*(buf + RU_count(number)))) <= delta)) &&
		((*Set1).count(RU_count(number)) != 1)) {
		check_for_local(RU_count(number), buf, Set1);

	}
	if ((*(buf + LC_count(number)) >= 1000) && (*(buf + LC_count(number)) <= 2000) &&
		(((*(buf + LC_count(number)) - *(buf + number)) <= delta) && (((*(buf + number)) - (*(buf + LC_count(number)))) <= delta)) &&
		((*Set1).count(LC_count(number)) != 1)) {
		check_for_local(LC_count(number), buf, Set1);

	}
	if ((*(buf + RC_count(number)) >= 1000) && (*(buf + RC_count(number)) <= 2000) &&
		(((*(buf + RC_count(number)) - *(buf + number)) <= delta) && (((*(buf + number)) - (*(buf + RC_count(number)))) <= delta)) &&
		((*Set1).count(RC_count(number)) != 1)) {
		check_for_local(RC_count(number), buf, Set1);

	}
	if ((*(buf + LD_count(number)) >= 1000) && (*(buf + LD_count(number)) <= 2000) &&
		(((*(buf + LD_count(number)) - *(buf + number)) <= delta) && (((*(buf + number)) - (*(buf + LD_count(number)))) <= delta)) &&
		((*Set1).count(LD_count(number)) != 1)) {
		check_for_local(LD_count(number), buf, Set1);

	}
	if ((*(buf + MD_count(number)) >= 1000) && (*(buf + MD_count(number)) <= 2000) &&
		(((*(buf + MD_count(number)) - *(buf + number)) <= delta) && (((*(buf + number)) - (*(buf + MD_count(number)))) <= delta)) &&
		((*Set1).count(MD_count(number)) != 1)) {
		check_for_local(MD_count(number), buf, Set1);

	}
	if ((*(buf + RD_count(number)) >= 1000) && (*(buf + RD_count(number)) <= 2000) &&
		(((*(buf + RD_count(number)) - *(buf + number)) <= delta) && (((*(buf + number)) - (*(buf + RD_count(number)))) <= delta)) &&
		((*Set1).count(RD_count(number)) != 1)) {
		check_for_local(RD_count(number), buf, Set1);
	}
}

std::set<int> find_local_max(UINT16* buf) {
	int number = 108799;
	int end_number = 217087;
	while (number < end_number) {
		UINT16 depth = (*(buf + number));
		number++;
		if ((depth >= 1900) & (depth < 2000)) {
			break;
		}
	}

	//number = 108800;
	std::set<int> Set1;
	Set1.insert(number);
	check_for_local(number, buf, &Set1);
	printf("OK");
	return Set1;
}

void getKinectData(GLubyte* dest) {
	IColorFrame* frame = NULL;
	if (SUCCEEDED(reader->AcquireLatestFrame(&frame))) {
		frame->CopyConvertedFrameDataToArray(width * height * 4, data, ColorImageFormat_Bgra);
	}
	if (frame) frame->Release();
}

void getKinectDepthData(GLubyte* dest) {

	IDepthFrame* frame_depth = NULL;
	printf("TRY TO GET DATA\n");

	if (SUCCEEDED(reader_depth->AcquireLatestFrame(&frame_depth))) {
		printf("ACCESS TO DEPTH\n");
		UINT sz;
		UINT16 *buf;
		frame_depth->AccessUnderlyingBuffer(&sz, &buf);

		frame_depth->CopyFrameDataToArray(sz, buf_depth);

		USHORT min;
		USHORT max;

		frame_depth->get_DepthMinReliableDistance(&min);
		frame_depth->get_DepthMaxReliableDistance(&max);

		//printf("%d\n", min);
		//printf("%d\n", max);

		UINT16* curr = (UINT16 *)buf_depth;
		UINT16* dataEnd = curr + (width * height);

		int min_depth = 2000;
		int max_depth = 0;
		int count_min_depth = 0;

		while (curr < dataEnd) {
			// Get depth in millimeters
			UINT16 depth = (*(curr++));

			if (depth < min_depth) {
				min_depth = depth;
			}
			if (depth > max_depth) {
				max_depth = depth;
			}
			if (depth <= 501) {
				count_min_depth++;
			}
			// Draw a grayscale image of the depth:
			// B,G,R are all set to depth%256, alpha set to 1.
			for (int i = 0; i < 3; ++i) {
				if (depth <= 500) {
					if (i < 2) {
						*dest++ = 0;
					}
					else {
						*dest++ = 255.0f;
					}
				}
				else {
					*dest++ = depth == 0 || depth > 2000 ? 0 : 255 - (USHORT)(((float)depth / 8000.0f) * 255.0f);
				}
				//*dest++ = depth == 0 || depth > 2000 ? 0 : 255 - (BYTE)(((float)depth / 4095.0f) * 255.0f);
			}
			*dest++ = 0xff;
			
		}
		//printf("%d\n", min_depth);
		//printf("%d\n", max_depth);
		//printf("%d\n", count_min_depth);

	}
	if (frame_depth) frame_depth->Release();
}

void local_maximum(GLubyte* dest) {		
	USHORT min;
	USHORT max;

	//printf("%d\n", min);
	//printf("%d\n", max);

	UINT16* curr = (UINT16*)buf_depth;
	UINT16* dataEnd = curr + (width * height);

	std::set<int> set1 = find_local_max(buf_depth);
	copy(set1.begin(), set1.end(), std::ostream_iterator<int>(std::cout, " "));

	/*std::set<int> set1;
	for (int i = 20000; i < 21000; i++) {
		set1.insert(i);
		printf("KEK");
	}*/
	//copy(set1.begin(), set1.end(), std::ostream_iterator<int>(std::cout, " "));

	int min_depth = 2000;
	int max_depth = 0;
	int count_min_depth = 0;
	int counter_pixel = 0;



	while (curr < dataEnd) {
		// Get depth in millimeters
		UINT16 depth = (*(curr++));

		if (depth < min_depth) {
			min_depth = depth;
		}
		if (depth > max_depth) {
			max_depth = depth;
		}
		if (depth <= 501) {
			count_min_depth++;
		}
		counter_pixel++;


		// Draw a grayscale image of the depth:
		// B,G,R are all set to depth%256, alpha set to 1.
		for (int i = 0; i < 3; ++i) {
			if (depth <= 500) {
				if (i < 2) {
					*dest++ = 0;
				}
				else {
					*dest++ = 255.0f;
				}
			}
			else if (set1.count(counter_pixel - 1) == 1) {
				if (i == 0)  {
					*dest++ = 255.0f;
				}
				else {
					*dest++ = 0;
				}
			}
			else {
				*dest++ = depth == 0 || depth > 2000 ? 0 : 255 - (USHORT)(((float)depth / 8000.0f) * 255.0f);
			}
			//*dest++ = depth == 0 || depth > 2000 ? 0 : 255 - (BYTE)(((float)depth / 4095.0f) * 255.0f);
		}
		*dest++ = 0xff;

	}
		//printf("%d", counter_pixel);
}

void drawKinectData(char type) {
	glBindTexture(GL_TEXTURE_2D, textureId);
	/*if (type == 'D') {
		getKinectDepthData(data);
	}
	else {
		getKinectData(data);
	}*/
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)data);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(width, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(width, height, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, height, 0.0f);
	glEnd();
}

void drawData() {
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)data);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(width, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(width, height, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, height, 0.0f);
	glEnd();
}

void execute(char type) {
	SDL_Event ev;
	bool running = true;
	int count = 0;
	//getKinectDepthData(data);
	while (running) {
		count++;
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_KEYDOWN) {
				printf("PAUSE\n");
				drawKinectData(type);
				SDL_GL_SwapBuffers();
				reader_depth->put_IsPaused(TRUE);
				printf("PRESS BUTTON ON KEYBOARD\n");
				//место для функции обработки данных, которая изменит data
				drawKinectData(type);
				SDL_GL_SwapBuffers();
				while (SDL_WaitEvent(&ev)){
					//local_maximum(data);
					//SDL_GL_SwapBuffers();
					if (ev.type == SDL_KEYDOWN) {
						reader_depth->put_IsPaused(FALSE);
						break;
					}
				}
				//local_maximum(data);
				//SDL_GL_SwapBuffers();
				printf("CONTINUE\n");
			}
			if (ev.type == SDL_QUIT) running = false;
		}
		if (count < 4) getKinectDepthData(data);
		drawKinectData(type);
		SDL_GL_SwapBuffers();
		Sleep(1000);
	}
}

int main(int argc, char* argv[]) {
	if (!init(argc, argv)) return 1;
	if (!initKinect()) return 1;
	if (!initKinectDepth()) return 1;

	// Initialize textures
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)data);
	glBindTexture(GL_TEXTURE_2D, 0);

	// OpenGL setup
	glClearColor(0, 0, 0, 0);
	glClearDepth(1.0f);
	glEnable(GL_TEXTURE_2D);

	// Camera setup
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, 1, -1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Main loop
	char type;
	type = 'D';
	execute(type);
	/*std::set<int> Set;
	for (int i = 0; i < 217080; i++) {
		Set.insert(10000);
	}*/
	return 0;
}
