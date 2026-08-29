module;

#include <string>

#include <memory>
#include <unordered_map>
#include <vector>

export module ffxi:system_dat;

import lotus;

// Importing the partitions that define these, rather than forward-declaring
// them here, keeps them a single entity. A declaration in one partition and a
// definition in another do not merge, and the two then fail to match wherever
// both are visible.
import :dat;
import :dat.generator;
import :dat.scheduler;

export class FFXIGame;

export class SystemDat
{
    struct _private_tag
    {
        explicit _private_tag() = default;
    };

public:
    static lotus::Task<std::unique_ptr<SystemDat>> Load(FFXIGame* game);

    std::unordered_map<std::string, FFXI::Generator*> generators;
    std::unordered_map<std::string, FFXI::Scheduler*> schedulers;

    SystemDat(FFXIGame* game, _private_tag);

private:
    FFXIGame* game{nullptr};

    SystemDat(const SystemDat&) = delete;
    SystemDat(SystemDat&&) = default;
    SystemDat& operator=(const SystemDat&) = delete;
    SystemDat& operator=(SystemDat&&) = default;

    lotus::Task<> ParseDir(FFXI::DatChunk*);

    std::vector<std::shared_ptr<lotus::Model>> generator_models;
    std::unordered_map<std::string, FFXI::Keyframe*> keyframes;
};
