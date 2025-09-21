#include "algernon/mesh/include/mesh.h"
#include "algernon/core/include/core.h"
#include "fastgltf/glm_element_traits.hpp"
#include "fastgltf/core.hpp"
#include "fastgltf/types.hpp"
#include "fastgltf/tools.hpp"
#include <algorithm>
#include <print>

namespace Algernon {

void GetModelProperties(const fastgltf::Asset &asset, std::size_t &vertices_count, std::size_t &indices_count) {
  for (const auto &mesh : asset.meshes) {
    for (const auto &primitive : mesh.primitives) {
      const auto position_attribute = primitive.findAttribute("POSITION");
      const auto &position_accessor = asset.accessors[position_attribute->accessorIndex];
      const auto &indices_accessor = asset.accessors[primitive.indicesAccessor.value()];
      vertices_count += position_accessor.count;
      indices_count += indices_accessor.count;
    }
  }
}

std::vector<Vector3f> GetModelVertices(const fastgltf::Asset &asset) {
  std::size_t vertices_offset = 0, vertices_count = 0, indices_count = 0;
  GetModelProperties(asset, vertices_count, indices_count);
  std::vector<Vector3f> out(vertices_count);
  for (const auto &mesh : asset.meshes) {
    for (const auto &primitive : mesh.primitives) {
      const auto position_attribute = primitive.findAttribute("POSITION");
      const auto &position_accessor = asset.accessors[position_attribute->accessorIndex];
      fastgltf::copyFromAccessor<Vector3f>(asset, position_accessor, out.data() + vertices_offset);
      vertices_offset += position_accessor.count;
    }
  }
  return out;
}

std::vector<uint32_t> GetModelIndices(const fastgltf::Asset &asset) {
  std::size_t vertices_offset = 0, index_offset = 0;
  std::size_t vertices_count = 0, indices_count = 0;
  GetModelProperties(asset, vertices_count, indices_count);
  std::vector<uint32_t> out(indices_count);
  for (const auto &mesh : asset.meshes) {
    for (const auto &primitive : mesh.primitives) {
      auto begin = out.begin() + index_offset;
      const auto &indices_accessor = asset.accessors[primitive.indicesAccessor.value()];
      const auto &position_accessor = asset.accessors[primitive.findAttribute("POSITION")->accessorIndex];
      fastgltf::iterateAccessor<uint32_t>(asset, indices_accessor, [&](uint32_t index) { *begin++ = index + vertices_offset; });
      vertices_offset += position_accessor.count;
      index_offset += indices_accessor.count;
    }
  }
  return out;
}

void Mesh::LoadGLTF(const std::filesystem::path &path) {

  auto extensions = fastgltf::Extensions::KHR_mesh_quantization | //
                    fastgltf::Extensions::KHR_texture_transform | //
                    fastgltf::Extensions::KHR_materials_variants; //

  auto options = fastgltf::Options::DontRequireValidAssetMember | //
                 fastgltf::Options::LoadExternalBuffers |         //
                 fastgltf::Options::GenerateMeshIndices;

  fastgltf::Parser parser(extensions);

  auto GLTF_file = fastgltf::MappedGltfFile::FromPath(path);

  auto asset = parser.loadGltf(GLTF_file.get(), path.parent_path(), options);

  vertices_ = GetModelVertices(asset.get());
  auto indices = GetModelIndices(asset.get());

  for (auto i = 0; i < indices.size(); i += 3) {
    auto i0 = indices[i];
    auto i1 = indices[i + 1];
    auto i2 = indices[i + 2];
    faces_.emplace_back(i0, i1, i2);
  }
}

} // namespace Algernon