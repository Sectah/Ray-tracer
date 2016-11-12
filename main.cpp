#include <iostream>
#include <fstream>
#include <algorithm>
#include <glm/glm.hpp>
#include <ppl.h>
#include <SDL.h>

#include "Shape.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "objloader.h"
#include "AAB.h"

using namespace std;
using namespace glm;

void createShapes();
vec3 rayTrace(vec3 p, vec3 v, int d);
void setPixel(SDL_Surface* surface);
bool drawPixel(SDL_Surface* surface, int i, int j, int x, int y, int z);

float height = 640.0f;
float width = 840.0f;

bool recurseReflect = false;
bool hardShadows = true;

float printOnce = 1;
float FOV = 90.0f;	
SDL_Event event = { 0 };

int maxDepth = 5;

vector<Shape*> shapeVector;

vec3 **image = new vec3*[width];

AAB* areaLight = new AAB(vec3(-4.5f, 20, -4.5f), vec3(9, 0.1f, 9));

bool drawPixel(SDL_Surface* surface, int x, int y, int r, int g, int b) {

	if (y < 0 || y >= height || x < 0 || x >= width) {
		return false;
	}

	Uint32 colorSDL = SDL_MapRGB(surface->format, r, g, b);
	Uint32* bufp;

	bufp = (Uint32*)surface->pixels + y * surface->pitch / 4 + x;
	*bufp = colorSDL;
	bufp += surface->pitch / 4;

	return true;
}

void setPixel(SDL_Surface* surface) {

	concurrency::parallel_for(int(0), (int)width, [&](int i) {
		for (int j = 0; j < height; ++j) {
			float pixNormX = (i + 0.5f) / width;
			float pixNormY = (j + 0.5f) / height;
			float imageAspectRatio = width / height;
			float pixRemapX = (2 * pixNormX - 1) * imageAspectRatio;
			float pixRemapY = 1 - 2 * pixNormY;
			float pixCameraX = pixRemapX * tan(radians(FOV) / 2);
			float pixCameraY = pixRemapY * tan(radians(FOV) / 2);
			vec3 PcameraSpace = vec3(pixCameraX, pixCameraY, -1);
			vec3 rayOrigin = vec3(0);
			vec3 rayDirection = normalize(PcameraSpace - rayOrigin);

			vec3 pixelColour = rayTrace(rayOrigin, rayDirection, 0);
			image[i][j] = pixelColour;
			drawPixel(surface, i, j, std::min(1.0f, image[i][j].x) * 255, std::min(1.0f, image[i][j].y) * 255, std::min(1.0f, image[i][j].z) * 255);
		}
	});
}

void createShapes() {

	//======================= SPHERES =======================

	shapeVector.push_back(new Plane(vec3(0, -4, 0), vec3(0, 1, 0), vec3(0.3f)));		
	shapeVector.push_back(new Sphere(vec3(0, 0, -20), 4, vec3(1, 0.32f, 0.36f)));		
	shapeVector.push_back(new Sphere(vec3(5, -1, -15), 2, vec3(0.9f, 0.76f, 0.46f)));	
	shapeVector.push_back(new Sphere(vec3(5, 0, -25), 3, vec3(0.65f, 0.77f, 0.97f)));	
	shapeVector.push_back(new Sphere(vec3(-5.5f, 0, -15), 3, vec3(0.9f)));				

	//======================================================

	////======================= TEAPOT =======================

	//shapeVector.push_back(new Plane(vec3(0, -2.8, 0), vec3(0, 1, 0), vec3(0.3f)));

	//vector<vec3> teaVertices;
	//vector<vec3> teaNormals;
	//bool loadTea = loadOBJ("Models/teapot_simple.obj", teaVertices, teaNormals);

	//for (int i = 0; i < teaVertices.size(); i++) {
	//	teaVertices[i].z -= 6;
	//	teaVertices[i].y -= 2;

	//}

	//for (int i = 0; i < teaVertices.size(); i += 3) {
	//	shapeVector.push_back(new Triangle(teaVertices[i], teaVertices[i + 1], teaVertices[i + 2], teaNormals[i], teaNormals[i + 1], teaNormals[i + 2], vec3(0, 0.6f, 1)));
	//}
	////======================================================
}

vec3 rayTrace(vec3 refRayOrigin, vec3 refRayDirection, int depth) {

	vec3 reflectColour, pixelColour;
	vec3 uvw, minUVW = vec3(0);

	float t0 = 0.0f;
	float minT = FLT_MAX;
	int shapeHit = -1;

	for (int k = 0; k < shapeVector.size(); ++k) {

		bool hit = shapeVector[k]->Intersection(refRayOrigin, refRayDirection, uvw.x, uvw.y, uvw.z, &t0);

		if (hit && t0 < minT) {
			minT = t0;
			minUVW.x = uvw.x;
			minUVW.y = uvw.y;
			minUVW.z = uvw.z;
			shapeHit = k;
		}
	}
	
	if (shapeHit != -1) {
		
		vec3 p0 = refRayOrigin + (minT * refRayDirection);

		vec3 areaLightPos = vec3(areaLight->position.x, areaLight->position.y, areaLight->position.z);
		vec3 areaLightSize = vec3(areaLight->size.x, areaLight->size.y, areaLight->size.z);
		vec3 areaLightCenter = vec3(areaLightPos.x + (areaLightSize.x / 2), areaLightPos.y + (areaLightSize.y / 2), areaLightPos.z + (areaLightSize.z / 2));
		vec3 lightIntensity = vec3(1);

		vec3 diffuseColour, specularColour = vec3(0);
		int shininess = 0;

		vec3 normal = normalize(shapeVector[shapeHit]->CalculateNormal(p0, minUVW.x, minUVW.y, minUVW.z, &shininess, &diffuseColour, &specularColour));

		vec3 ambient = shapeVector[shapeHit]->colour * vec3(0.07f);

		vec3 lightRay = normalize(areaLightCenter - p0);
		vec3 diffuse = diffuseColour * lightIntensity * glm::max(0.0f, dot(lightRay, normal));

		vec3 reflection = normalize(2 * (dot(lightRay, normal)) * normal - lightRay);
		float maxCalc = glm::max(0.0f, dot(reflection, normalize(refRayOrigin - p0)));
		vec3 specular = specularColour * lightIntensity * pow(maxCalc, shininess);

		if (recurseReflect) {

			if ((depth < maxDepth) && (shininess > 0)) {

				vec3 reflectionRayDirection = refRayDirection - 2 * dot(refRayDirection, normal) * normal;
				vec3 reflectionRayOrigin = p0 + (normal * 1e-4f);
				reflectColour = reflectColour + 0.25f * rayTrace(reflectionRayOrigin, reflectionRayDirection, depth + 1);
				return pixelColour = diffuse + specular + reflectColour;
			}
		} 

		int lightShapeHit = -1;

		if (hardShadows) {

			for (int l = 0; l < shapeVector.size(); ++l) {

				bool lightingHit = shapeVector[l]->Intersection(p0 + (1e-4f * normal), lightRay, uvw.x, uvw.y, uvw.z, &t0);

				if (lightingHit && t0 < minT) {
					minT = t0;
					lightShapeHit = l;
				}
			}

			if (lightShapeHit != -1) {

				pixelColour = ambient;
			}
			else {

				pixelColour = (diffuse + specular);
			}
		}
		
		else {
			
			float sample = 9.0f;
			float softIncrement = areaLightSize.x / sample;
			float hitRays = 1.0f;
			float totalRays = 0.0f;

			totalRays = pow(sample, 2);

			for (float m = 0; m < areaLightSize.x; m += softIncrement) {

				for (float n = 0; n < areaLightSize.z; n += softIncrement) {

					float t0s = 0.0f;
					float minTs = FLT_MAX;
					lightShapeHit = -1;

					vec3 UVWs = vec3(0);

					areaLightPos = vec3(m, areaLightPos.y, n);
					lightRay = normalize(areaLightPos - p0);

					for (int l = 0; l < shapeVector.size(); ++l) {

						if (shapeHit != l) {

							bool lightingHit = shapeVector[l]->Intersection(p0 + (1e-4f * normal), lightRay, UVWs.x, UVWs.y, UVWs.z, &t0s);

							if (lightingHit && t0s < minTs) {

								minTs = t0s;
								lightShapeHit = l;
							}
						}
					}

					if (lightShapeHit != -1) {

						hitRays = hitRays - (1 / totalRays);
					}
				}
			}

			pixelColour = vec3((hitRays) * (diffuse + specular));
		}
	}
	else {

		pixelColour = vec3(0.1, 0.2, 0.3);
	}

	return pixelColour;
}

bool done(bool quit_if_esc, bool delay) {

	if (delay) {
		SDL_Delay(5);
	}

	bool done = false;

	if (!SDL_PollEvent(&event)) {
		return 0;
	}

	if (event.type == SDL_QUIT) {
		done = true;
	}

	else if (event.type == SDL_KEYDOWN) {

		switch (event.key.keysym.sym) {

		case SDLK_ESCAPE:
			done = true;
			break;

		default:
			break;
		}
	}

	return done;
}

int main(int argc, char* args[]) {

	for (int i = 0; i < width; ++i) {
		image[i] = new vec3[height];
	}

	SDL_Window* window = NULL;

	SDL_Surface* screenSurface = NULL;

	window = SDL_CreateWindow("Ray Tracing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	screenSurface = SDL_GetWindowSurface(window);

	while (!done(true, false)) {

		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 0));

		createShapes();
		setPixel(screenSurface);

		SDL_UpdateWindowSurface(window);

		if (printOnce == 1) {
			printOnce = 0;
			cout << "Press s to toggle hard/soft shadows\n(Soft shadows will be laggy)\n\n" << "Press space to toggle between teapot and spheres\n\n" << "Press r to toggle the reflection\n\n" << "Use up and down to change the FOV\n" << endl;
		}

		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_UP:
				if (FOV > 20.0f) FOV -= 10.0f;
				cout << "Decreasing the FOV\n";
				break;

			case SDLK_DOWN:
				if (FOV < 150.0f) FOV += 10.0f;
				cout << "Increasing the FOV\n";
				break;

			case SDLK_s:
				hardShadows = !hardShadows;
				cout << "Switching the shadows, please wait...\n";
				break;

			case SDLK_r:
				recurseReflect = !recurseReflect;
				cout << "Switching the reflections, please wait...\n";
				break;

			default:
				break;
			}
		}
	}

	SDL_DestroyWindow(window);

	SDL_Quit();

	delete areaLight;

	for (int i = 0; i < width; ++i) {
		delete[] image[i];
	}
	delete[] image;

	for (int i = 0; i < shapeVector.size(); ++i) {
		delete shapeVector[i];
	}

	return 0;
}
