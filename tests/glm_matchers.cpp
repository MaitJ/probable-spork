#include <catch2/catch.hpp>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

template <typename GlmVecVector>
class IsGlmVecsEqualMatcher : public Catch::MatcherBase<GlmVecVector> {
    GlmVecVector vecs;

public:
    IsGlmVecsEqualMatcher(GlmVecVector vertices) : vecs{vertices} {}

    bool match(GlmVecVector const& in) const override {
        bool equals = true;
        for (int i = 0; i < vecs.size(); ++i) {
            for (int j = 0; j < vecs[i].length(); ++j) {
                if (in[i][j] != vecs[i][j]) {
                    equals = false;
                }
            }
        }
        return equals;
    }

    std::string describe() const override {
        std::ostringstream ss;
        ss << "Vectors are not equal";
        return ss.str();
    }
};

template <typename T>
IsGlmVecsEqualMatcher<T> IsGlmVecsEqual(T vecs) {
    return {vecs};
}

template <typename GlmVec>
class IsGlmVecEqualMatcher : public Catch::MatcherBase<GlmVec> {
    GlmVec vector;

public:
    IsGlmVecEqualMatcher(GlmVec vector) : vector{vector} {}

    bool match(GlmVec const& in) const override {
        return (in.x == vector.x &&
                in.y == vector.y &&
                in.z == vector.z);
    }

    std::string describe() const override {
        std::ostringstream ss;
        ss << "Vectors are not equal";
        return ss.str();
    }
};

template <typename T>
IsGlmVecEqualMatcher<T> IsGlmVecEqual(T vector) {
    return {vector};
}


namespace Catch {
    template<>
    struct StringMaker<glm::vec3> {
        static std::string convert(glm::vec3 const& value) {
            return glm::to_string(value);
        }
    };

    template<>
    struct StringMaker<glm::vec2> {
        static std::string convert(glm::vec2 const& value) {
            return glm::to_string(value);
        }
    };
}
