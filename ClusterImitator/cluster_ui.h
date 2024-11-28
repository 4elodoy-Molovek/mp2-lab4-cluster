#pragma once

class Cluster;

class ClusterUI
{
private:
    bool renderEnabled;

public:
    ClusterUI() : renderEnabled(false) {}
    void EnableRendering(bool enable = true)
    {
        renderEnabled = enable;
    }
    bool IsRenderingEnabled() const
    {
        return renderEnabled;
    }
    void RenderCluster(const Cluster& c);
};