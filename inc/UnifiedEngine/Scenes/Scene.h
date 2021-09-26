#pragma once

//Includes
#include "../Object/GameObject.h"
#include "../Object/Skybox.h"
#include "../Core/Renderer/Camera.h"
#include "../UI/Canvas.h"

namespace UnifiedEngine {
	//Transitioning
	enum Transition_Type {
		None = 0,
		Fade,
		Block,
		Swipe,
		Custom,
	};

	//To Do in a future date
	class Transition {
	private:
		Transition_Type Type;
	public:
		Transition(Transition_Type type) {
			this->Type = type;
		}
	};

	//Main scene
	class Scene {
	public:
		//Scene Objects
		Camera MainCamera;
		vector<GameObject*> gameObjects;
		Skybox skybox;
		Canvas UI;

		//GObject Loading
		void Instantiate(GameObject* Object) {
			GameObject* NewObject = new GameObject(*Object);
			this->gameObjects.push_back(NewObject);
		}

		//Destroy Object if it exists
		void Destroy(GameObject* Object) {
			//Indexing
			int index = -1;
			int iterator = 0;
			//Find idex
			for (GameObject* G : this->gameObjects) {
				if (G == Object) {
					index = iterator;
				}
				iterator++;
			}

			//Remove if valid
			if (index != -1) {
				this->gameObjects.erase(this->gameObjects.begin() + index);
			}
		}

		//Look for object with a name
		GameObject* FindObjectWithName(const char* name) {
			//Looping
			for (GameObject* G : this->gameObjects) {
				if (G->Name == name) {
					return G;
				}
			}
		}

		//Object with a tag
		GameObject* FindObjectWithTag(const char* tag) {
			//Looping
			for (GameObject* G : this->gameObjects) {
				if (G->Tag == tag) {
					return G;
				}
			}
		}

		//Multiple Objects with a Name
		vector<GameObject*> FindObjectsWithName(const char* name) {
			//For return
			vector<GameObject*> ret;
			//Looping and appending to the vector
			for (GameObject* G : this->gameObjects) {
				if (G->Name == name) {
					ret.push_back(G);
				}
			}
			return ret;
		}

		//Multiple objects with a Tag
		vector<GameObject*> FindObjectsWithTag(const char* tag) {
			//For return
			vector<GameObject*> ret;
			//Looping and appending to the vector
			for (GameObject* G : this->gameObjects) {
				if (G->Tag == tag) {
					ret.push_back(G);
				}
			}
			return ret;
		}
	};
}