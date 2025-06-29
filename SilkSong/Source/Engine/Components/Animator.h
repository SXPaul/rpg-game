/**
 * @file	Animator.h
 * @brief	���������붯��������ݵĹ����߼�
 * @author	Arty
 **/




#pragma once
#include"ActorComponent.h"





/* ����ί�� */
DECLARE_NO_PARAM_UNICAST_DELEGATE_CLASS(AnimationDelegate)


class IMAGE;
class Animator;
class AnimEdge;
class ImageInterface;



/*----------------------------------
			   ����Դ
  ----------------------------------*/
class Animation final :public TimerHandler
{
    friend Animator;
	friend AnimEdge;

	Animator* animController = nullptr;
	int32 num = 0;//����֡��
	FVector2D offset = {0,0};//ƫ����
	IMAGE** images = nullptr;//����֡����
	int32 index = 0;//��ǰ֡����
	bool bLooping = true;//�Ƿ��ѭ������
	bool bReverse = false;//�Ƿ��򲥷�
	bool bMontage = false;//�Ƿ�����̫�沥��

	Timer clock;//��ʱ��

	std::unordered_map<int32, AnimationDelegate>notifications;//�Զ��嶯��֪ͨ

	std::list<AnimEdge*>nexts;//������

	void Tick();

public:
	Animation() { clock.Bind(0, this, &Animation::Tick, true); clock.Stop();}

	//���ض�����Դ
	void Load(std::string name, FVector2D delta = {0,0});

	//���ö���֡���ʱ��
	void SetInterval(double interval) { clock.SetDelay(interval); }

	//���ö���֡�±�
	void SetIndex(int32 i) { index = i; }

	//��ȡ����֡�±�
	int32 GetIndex()const { return index; }

	//�����Ƿ�ѭ������
	void SetLooping(bool loop) { bLooping = loop; }

	//��ָ��֡����Ӷ���֪ͨ
	void AddNotification(int32 index, const AnimationDelegate& event) { notifications.insert({ index,event }); }

	//��ȡ�Ƿ��򲥷�
	bool IsReverse()const { return bReverse; }

	//�����Ƿ��򲥷�
	void SetReverse(bool bIsReverse) { bReverse = bIsReverse; }

	AnimationDelegate OnAnimEnter;//���붯���¼�
	AnimationDelegate OnAnimExit;//�뿪�����¼�

private:
	AnimationDelegate OnMontageExit;//��̫������¼������ڼ�¼������̫��ǰһ���������Ա��ڵ���̫���޺�̽ڵ�ʱ�������¼��Ӷ��ָ�ǰһ��������

	bool exitLock = false;//����������������ȷ����һ�������ڵ�OnAnimExitִֻ��һ�Σ���ֹ���޵ݹ�
};







/* ת�������Ƚ� */
enum class TransitionComparison : uint8
{
	Equal,
	NotEqual,
	Greater,
	Less,
	GreaterEqual,
	LessEqual
};


/* ����ת������ */
namespace AnimTransition
{
	struct Integer 
	{
		std::string paramName;
		int32 value;
		TransitionComparison comparison;
	};

	struct Float 
	{
		std::string paramName;
		float value;
		TransitionComparison comparison;
	};

	struct Bool 
	{
		std::string paramName;
		bool value;
	};

	struct Trigger
	{
		std::string paramName;
	};

	enum ComparisonMode
	{
		AND,OR
	};

	template<typename T>
	bool GetComparisonResult(T a, T b, TransitionComparison comp)
	{
		switch (comp) {
		case TransitionComparison::Equal:return a == b;
		case TransitionComparison::Greater:return a > b;
		case TransitionComparison::GreaterEqual:return a >= b;
		case TransitionComparison::Less:return a < b;
		case TransitionComparison::LessEqual:return a <= b;
		case TransitionComparison::NotEqual:return a != b;
		}
		return false;
	}
}


/*----------------------------------
			��������(�����)
  ----------------------------------*/
class AnimEdge final
{
	friend Animator;
	friend void Animation::Tick();

	Animation* start;
	Animation* end;

	std::vector<AnimTransition::Integer> integerConditions;
	std::vector<AnimTransition::Float> floatConditions;
	std::vector<AnimTransition::Bool> boolConditions;
	std::vector<AnimTransition::Trigger> triggerConditions;

	AnimTransition::ComparisonMode comparisonMode;

public:
	AnimEdge() :start{}, end{}, comparisonMode(AnimTransition::ComparisonMode::AND) {}

	/**
	 * @brief �������ɳ�ʼ��
	 * @param[in] start			    �����ڵ�
	 * @param[in] end	            ����ڵ�
	 * @param[in] mode              ���ɱȽ�ģʽ��AND��Ҫ��������������ORֻ����������������
	 **/
	void Init(Animation& start, Animation& end, AnimTransition::ComparisonMode mode = AnimTransition::AND)
	{
		this->start = &start; this->end = &end; comparisonMode = mode; this->start->nexts.push_back(this);
	}

	//��ӹ�������
	void AddCondition(const AnimTransition::Integer& condition) 
	{
		integerConditions.push_back(condition);
    }
	void AddCondition(const AnimTransition::Float& condition)
	{
	    floatConditions.push_back(condition);
	}
	void AddCondition(const AnimTransition::Bool& condition)
	{
		boolConditions.push_back(condition);
	}
	void AddCondition(const AnimTransition::Trigger& condition)
	{
		triggerConditions.push_back(condition);
	}

	//�Ƿ��޹�������
	bool IsUnconditional()const 
	{ 
		return integerConditions.empty() && floatConditions.empty() && boolConditions.empty() && triggerConditions.empty();
	}
};








/* ״̬�������� */
enum class ParamType: uint8
{
	Integer, Bool, Float, Trigger
};


/*----------------------------------
			  ����������
  ----------------------------------*/
class Animator :public ActorComponent
{
	DEFINE_SUPER(ActorComponent)

    friend ImageInterface;
public:
	virtual ~Animator();
	virtual void BeginPlay() override;
	virtual void Update(float deltaTime) override;

	virtual void Activate()override;
	virtual void Deactivate()override;

	//���붯���ڵ�
	void Insert(std::string name, Animation& ani);

	//���ö����ڵ�(�������ϤAnimator�ܹ�������ֱ��ʹ��)
	void SetNode(std::string nodeName);

	//���ö����ڵ�(�������ϤAnimator�ܹ�������ֱ��ʹ��)
	void SetNode(Animation* node);

	//�Ƿ��ڲ���ĳ����
	bool IsPlaying(std::string nodeName);

	//���ø�����Ⱦ��
	void SetupAttachment(ImageInterface* renderer);

	//���Ŷ�����̫��Ƭ��
	void PlayMontage(std::string nodeName);

	//��Ӳ���
	void AddParamater(std::string paramName, ParamType type);

	//����int����
	void SetInteger(std::string paramName, int32 value);

	//����float����
	void SetFloat(std::string paramName, float value);

	//����bool����
	void SetBool(std::string paramName, bool value);

	//����������
	void SetTrigger(std::string paramName);

	//��ȡint����
	int32 GetInteger(std::string paramName);

	//��ȡfloat����
	float GetFloat(std::string paramName);

	//��ȡbool����
	bool GetBool(std::string paramName);

	//�Ƿ���Ϲ�������
	bool CheckConditions(AnimEdge* edge);

	//��ȡ��ǰ�����ٶ�
	float GetStep()const { return step; }

	//���ò����ٶ�
	void SetStep(float value) { step = value; }

private:
	std::unordered_map<std::string, Animation&> animations;

	std::unordered_map<std::string, int> paramatersInteger;
	std::unordered_map<std::string, float> paramatersFloat;
	std::unordered_map<std::string, bool> paramatersBool;
	std::unordered_map<std::string, bool> paramatersTrigger;

	Animation* aniNode = nullptr;//��ǰ���ŵĶ���

	Animation* lastNode = nullptr;//������̫��ǰ�Ķ���

	ImageInterface* rendererAttached = nullptr;//���ŵ���Ⱦ��

	IMAGE* currentSprite = nullptr;//��ǰ���ŵ�ͼ��

	float step = 1.f;//�����ٶ�
};