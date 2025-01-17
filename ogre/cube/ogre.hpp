void ogre_textures_define(int index, int number_of_mipmaps, int mip, int width, int height, int bpp, void* texture_image_data);
void ogre_textures_clear(void);

void ogre_objects_init(unsigned number_of_objects, const OBJECT_3D* objects);
void ogre_objects_clear(void);

#include "ogre_scenes.hpp"

void ogre_scenes_init(int number_of_scenes, const OBJECT_3D_SCENE_DATABASE_ENTRY* objects_3d_scene_database, SceneManager* sman);
void ogre_scenes_clear(void);
void ogre_scene_create(int scene_number, GameObjectScene& scene, SceneNode* root, SceneManager* mgr);

void ogre_terrain_init(Camera* camera, SceneManager* mgr);
void ogre_terrain_clear(void);
void ogre_terrain_update(void);
void ogre_terrain_tree(const OBJECT_3D& o);
void ogre_terrain_tree_clear(void);
