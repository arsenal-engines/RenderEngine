#pragma once

#include "Common.h"
#include <boost\preprocessor\variadic\size.hpp>
#include <boost\preprocessor\variadic\elem.hpp>
#include <boost\preprocessor\variadic\to_list.hpp>
#include <boost\preprocessor\list\for_each.hpp>

// https://msdn.microsoft.com/en-us/library/windows/desktop/bb509647(v=vs.85).aspx
#define VS_SEMANTIC_INDEX_BINORMAL			0
#define VS_SEMANTIC_INDEX_BLENDINDICES		1
#define VS_SEMANTIC_INDEX_BLENDWEIGHT		2
#define VS_SEMANTIC_INDEX_COLOR				3
#define VS_SEMANTIC_INDEX_NORMAL			4
#define VS_SEMANTIC_INDEX_POSITION			5
#define VS_SEMANTIC_INDEX_POSITIONT			6
#define VS_SEMANTIC_INDEX_PSIZE				7
#define VS_SEMANTIC_INDEX_TANGENT			8
#define VS_SEMANTIC_INDEX_TEXCOORD			9

#define VS_SEMANTICS_TYPES \
XMFLOAT4, UINT, FLOAT, XMFLOAT4, XMFLOAT3, \
XMFLOAT4, XMFLOAT4, FLOAT, XMFLOAT4, XMFLOAT2

#define VS_SEMANTICS_FORMATS \
DXGI_FORMAT_R32G32B32A32_FLOAT, \
DXGI_FORMAT_R32_UINT, \
DXGI_FORMAT_R32_FLOAT, \
DXGI_FORMAT_R32G32B32A32_FLOAT, \
DXGI_FORMAT_R32G32B32_FLOAT, \
DXGI_FORMAT_R32G32B32A32_FLOAT, \
DXGI_FORMAT_R32G32B32A32_FLOAT, \
DXGI_FORMAT_R32_FLOAT, \
DXGI_FORMAT_R32G32B32A32_FLOAT, \
DXGI_FORMAT_R32G32_FLOAT

#define VS_SEMANTIC_TYPE(SEMANTIC) BOOST_PP_VARIADIC_ELEM(VS_SEMANTIC_INDEX_ ## SEMANTIC, VS_SEMANTICS_TYPES)
#define VS_SEMANTIC_FORMAT(SEMANTIC) BOOST_PP_VARIADIC_ELEM(VS_SEMANTIC_INDEX_ ## SEMANTIC, VS_SEMANTICS_FORMATS)

#define VS_SEMANTIC_DECLARATION(R, DATA, SEMANTIC) VS_SEMANTIC_TYPE(SEMANTIC) SEMANTIC;
#define VS_SEMANTICS_DECLARATION(...) BOOST_PP_LIST_FOR_EACH(VS_SEMANTIC_DECLARATION, _, BOOST_PP_VARIADIC_TO_LIST(__VA_ARGS__))

#define VERTEX_STRUCT_DECLARATION(MATERIAL, ...)		\
		struct Vertex ## MATERIAL {						\
			VS_SEMANTICS_DECLARATION(__VA_ARGS__)		\
		};

#define MATERIAL_VARIABLE_DECLARATION(R, DATA, NAME)	\
		public:											\
            Variable& NAME() const;						\
		private:										\
            Variable* m_ ## NAME;
#define MATERIAL_VARIABLES_DECLARATION(...) BOOST_PP_LIST_FOR_EACH(MATERIAL_VARIABLE_DECLARATION, _, BOOST_PP_VARIADIC_TO_LIST(__VA_ARGS__))

#define MATERIAL_VARIABLE_DEFINITION(R, MATERIAL, NAME)	\
        Variable& MATERIAL::NAME() const {				\
            return *m_ ## NAME;							\
        }
#define MATERIAL_VARIABLES_DEFINITION(MATERIAL, ...) BOOST_PP_LIST_FOR_EACH(MATERIAL_VARIABLE_DEFINITION, MATERIAL, BOOST_PP_VARIADIC_TO_LIST(__VA_ARGS__))

#define MATERIAL_VARIABLE_INITIALIZATION(R, DATA, NAME) m_ ## NAME {},
#define MATERIAL_VARIABLES_INITIALIZATION(...) BOOST_PP_LIST_FOR_EACH(MATERIAL_VARIABLE_INITIALIZATION, _, BOOST_PP_VARIADIC_TO_LIST(__VA_ARGS__))

#define MATERIAL_VARIABLE_RETRIEVE(R, DATA, NAME) m_ ## NAME = m_effect->variable(#NAME);
#define MATERIAL_VARIABLES_RETRIEVE(...) BOOST_PP_LIST_FOR_EACH(MATERIAL_VARIABLE_RETRIEVE, _, BOOST_PP_VARIADIC_TO_LIST(__VA_ARGS__))

/*
typedef struct D3D11_INPUT_ELEMENT_DESC {
	LPCSTR SemanticName;
	UINT SemanticIndex;
	DXGI_FORMAT Format;
	UINT InputSlot;
	UINT AlignedByteOffset;
	D3D11_INPUT_CLASSIFICATION InputSlotClass;
	UINT InstanceDataStepRate;
} 	D3D11_INPUT_ELEMENT_DESC;
*/
#define GENERATE_INPUT_ELEMENT_DESC_ENTRY(R, DATA, SEMANTIC)\
	{#SEMANTIC, 0, VS_SEMANTIC_FORMAT(SEMANTIC), 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
#define GENERATE_INPUT_ELEMENT_DESC(...) BOOST_PP_LIST_FOR_EACH(GENERATE_INPUT_ELEMENT_DESC_ENTRY, _, BOOST_PP_VARIADIC_TO_LIST(__VA_ARGS__))

namespace Library {

	class EffectHelper {

	public:
		EffectHelper() = delete;
		EffectHelper(const EffectHelper&) = delete;
		EffectHelper& operator=(const EffectHelper&) = delete;

	};

}