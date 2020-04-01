#pragma once

#include "MathUtil.h"
#include "Drawable.h"
#include "Resource.h"
#include "ResourceManager.h"

namespace ToolKit
{

  class Texture;
  class Vertex;
  class Surface;

  struct SpriteEntry
  {
    std::string name;
    glm::vec2 offset;
    Rect<int> rectangle;
  };

  class SpriteSheet : public Resource
  {
  public:
    SpriteSheet();
    SpriteSheet(std::string file);
    ~SpriteSheet();

    virtual void Load() override;
    virtual void Init(bool flushClientSideArray = true) override;
		virtual void UnInit() override;

  private:
    bool FetchEntries();
    std::vector<Vertex> CreateQuat(SpriteEntry val);

  public:
    std::shared_ptr<Texture> m_spriteSheet;
    std::vector<SpriteEntry> m_entries;
    std::string m_imageFile;
    int m_imageWidth;
    int m_imageHeight;

  public:
    std::unordered_map<std::string, ToolKit::Surface*> m_sprites;
  };

  class SpriteAnimation : public Drawable
  {
  public:
    SpriteAnimation();
    SpriteAnimation(std::shared_ptr<SpriteSheet> spriteSheet);
    ~SpriteAnimation();

    virtual EntityType GetType() const;
    Surface* GetCurrentSurface();
    void Update(float deltaTime);

  public:
    float m_animFps = 23.4f;
    bool m_looping = false;
    bool m_animationStoped = false;
    std::vector<std::string> m_frames;
    std::shared_ptr<SpriteSheet> m_sheet;
    std::string m_currentFrame;

  private:
    float m_currentTime = 0.0f; // Seconds
    float m_prevTime = 0.0f;
  };

  class SpriteSheetManager : public ResourceManager<SpriteSheet>
  {
  };

}