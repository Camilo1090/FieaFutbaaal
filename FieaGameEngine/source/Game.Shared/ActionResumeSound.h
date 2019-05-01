#pragma once

#include "Action.h"
#include "bass.h"
#include "Factory.h"

namespace FieaGameEngine
{
	class ActionResumeSound : public Action
	{
		RTTI_DECLARATIONS(ActionResumeSound, Action)

	public:
		static const std::string FilePath;
		static const std::string IsSoundEffect;
		static Vector<Signature> Signatures();

	public:
		explicit ActionResumeSound(const std::string& name = std::string());
		virtual ~ActionResumeSound() = default;

		virtual gsl::owner<ActionResumeSound*> Clone() const override;
		virtual void Update(WorldState& worldState);

	private:

		std::string mFilePath;
		int mIsSoundEffect;
		HSAMPLE* mSample;
	};

	CONCRETE_FACTORY(ActionResumeSound, Action)
}


