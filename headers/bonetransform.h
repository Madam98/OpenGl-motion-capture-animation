#pragma once
#ifndef BONE_TRANSFORM_H

//**************************************************************************************
//****************BONE TRANSFORM********************************************************
//**************************************************************************************

const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const string NodeName)
{
	for (int i = 0; i < pAnimation->mNumChannels; i++) {
		const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];
		if (string(pNodeAnim->mNodeName.data) == NodeName) {
			return pNodeAnim;
		}
	}
	return NULL;
}

int FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	for (int i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++) {
		if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime) {
			return i;
		}
	}
	//assert(0);
	return 0;
}

int FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	assert(pNodeAnim->mNumRotationKeys > 0);
	for (int i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++) {
		if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime) {
			return i;
		}
	}
	//assert(0);
	return 0;
}

int FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	assert(pNodeAnim->mNumScalingKeys > 0);

	for (int i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++) {
		if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime) {
			return i;
		}
	}
	//assert(0);
	return 0;
}

void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	if (pNodeAnim->mNumScalingKeys == 1) {
		Out = pNodeAnim->mScalingKeys[0].mValue;
		return;
	}

	int ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
	int NextScalingIndex = (ScalingIndex + 1);
	assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
	float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
	float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
	//assert(Factor >= 0.0f && Factor <= 1.0f);
	const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
	const aiVector3D& End = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
	aiVector3D Delta = End - Start;
	Out = Start + Factor * Delta;
}

void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	// we need at least two values to interpolate...
	if (pNodeAnim->mNumRotationKeys == 1) {
		Out = pNodeAnim->mRotationKeys[0].mValue;
		return;
	}
	int RotationIndex = FindRotation(AnimationTime, pNodeAnim);
	int NextRotationIndex = (RotationIndex + 1);
	assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
	float DeltaTime = (float)(pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime);
	float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
	//assert(Factor >= 0.0f && Factor <= 1.0f);
	const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
	const aiQuaternion& EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
	aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
	Out = Out.Normalize();
}

void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	if (pNodeAnim->mNumPositionKeys == 1) {
		Out = pNodeAnim->mPositionKeys[0].mValue;
		return;
	}
	int PositionIndex = FindPosition(AnimationTime, pNodeAnim);
	int NextPositionIndex = (PositionIndex + 1);
	assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
	float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
	float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
	//assert(Factor >= 0.0f && Factor <= 1.0f);
	const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
	const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
	aiVector3D Delta = End - Start;
	Out = Start + Factor * Delta;
}

void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const glm::mat4& ParentTransform, const aiScene* scene, bool create)
{
	std::string NodeName(pNode->mName.data);
	const aiAnimation* pAnimation = scene->mAnimations[0];
	glm::mat4 nodeTransform(1.f);
	
	const aiNodeAnim* pNodeAnim = NULL;
	if (create) {
		pNodeAnim = FindNodeAnim(pAnimation, NodeName);
		//if (pNodeAnim != NULL)
		VertexBoneName temp = { pNodeAnim, NodeName };
		bonesNames.push_back(temp);
	}
	else {
		pNodeAnim = bonesNames[bonesNamesIndex].bonesNodeNames;
		NodeName = bonesNames[bonesNamesIndex].bonesStringNames;
		bonesNamesIndex++;
	}

	//const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);
	if (pNodeAnim) {
		aiVector3D Translation;
		CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
		nodeTransform = glm::translate(nodeTransform, glm::vec3(Translation.x, Translation.y, Translation.z));

		aiQuaternion RotationQ;
		CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);

		glm::quat qu = glm::quat(RotationQ.w,
			RotationQ.x,
			RotationQ.y,
			RotationQ.z);
		// Interpolate translation and generate translation transformation matrix
		nodeTransform *= glm::mat4_cast(qu);

		aiVector3D Scaling;
		CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);

		nodeTransform = glm::scale(nodeTransform, glm::vec3(Scaling.x, Scaling.y, Scaling.z));
	}
	
	glm::mat4 GlobalTransformation = ParentTransform * nodeTransform;


	if (m_BoneMapping.find(NodeName) != m_BoneMapping.end()) {
		int BoneIndex = m_BoneMapping[NodeName].first;
		m_BoneInfo[BoneIndex].FinalTransformation = GlobalTransformation *
			m_BoneInfo[BoneIndex].BoneOffset;
	}
	for (int i = 0; i < pNode->mNumChildren; i++) {
		ReadNodeHeirarchy(AnimationTime, pNode->mChildren[i], GlobalTransformation, scene, create);
	}
}

void BoneTransform(float TimeInSeconds, vector<glm::mat4>& Transforms, const aiScene* scene, bool create)
{
	float TicksPerSecond = 25.0f;
	float TimeInTicks = TimeInSeconds * TicksPerSecond;
	float AnimationTime = fmod(TimeInTicks, scene->mAnimations[0]->mDuration);
	ReadNodeHeirarchy(AnimationTime, scene->mRootNode, GIT2, scene, create);
	Transforms.resize(m_NumBones);
	for (int i = 0; i < m_NumBones; i++) {
		Transforms[i] = m_BoneInfo[i].FinalTransformation;
	}
}

#endif 