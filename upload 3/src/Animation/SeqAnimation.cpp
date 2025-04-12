#include "SeqAnimation.h"
#include "../Vendor/tinyxml2/tinyxml2.h"
#include "iostream"
#include "TextureManager.h"

SeqAnimation::SeqAnimation(bool repeat) : Animation(repeat) {}

void SeqAnimation::DrawFrame(float x, float y, float xScale, float yScale, SDL_RendererFlip flip) {
    TextureManager::GetInstance()->Draw(
        m_CurrentSeq.TextureIDs[m_CurrentFrame], x, y,
        m_CurrentSeq.Width, m_CurrentSeq.Height,
        xScale, yScale, flip
    );
}

void SeqAnimation::Update(float dt) {
    if (m_Repeat || !m_IsEnded) {
        m_IsEnded = false;
        m_CurrentFrame = (SDL_GetTicks() / m_CurrentSeq.Speed) % m_CurrentSeq.FrameCount;
    }

    if (m_Repeat && m_CurrentFrame == (m_CurrentSeq.FrameCount - 1)) {
        m_IsEnded = true;
        m_CurrentFrame = m_CurrentSeq.FrameCount - 1;
    }
}

void SeqAnimation::SetCurrentSeq(std::string seqID) {
    if (m_SegMap.count(seqID) > 0) {
        m_CurrentSeq = m_SegMap[seqID];
    } else {
        std::cout << "The given Sequence animation is not matching: " << seqID << std::endl;
    }
}

void SeqAnimation::Parse(std::string source) {
    tinyxml2::XMLDocument xml;
    if (xml.LoadFile(source.c_str()) != tinyxml2::XML_SUCCESS) {
        std::cout << "Failed to load animation file: " << source << std::endl;
        return;
    }

       tinyxml2::XMLElement* root = xml.RootElement();
    if (!root) {
        std::cout << "No root element found in: " << source << std::endl;
        return;
    }

    for (tinyxml2::XMLElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (strcmp(e->Value(), "sequence") == 0) {
            Sequence seq;
            const char* seqID = e->Attribute("id");
            if (!seqID) continue;

            e->QueryIntAttribute("speed", &seq.Speed);
            e->QueryIntAttribute("width", &seq.Width);
            e->QueryIntAttribute("height", &seq.Height);
            e->QueryIntAttribute("frameCount", &seq.FrameCount);

            for (tinyxml2::XMLElement* frame = e->FirstChildElement(); frame != nullptr; frame = frame->NextSiblingElement()) {
                const char* textureID = frame->Attribute("textureID");
                if (textureID) {
                    seq.TextureIDs.push_back(textureID);
                }
            }
            m_SegMap[seqID] = seq;
        }
    }
}

