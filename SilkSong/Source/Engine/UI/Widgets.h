/**
 * @file	Widgets.h
 * @brief   ��������uiС�����Ķ��壬�ṩ��һЩ������uiСģ��
 * @author	Arty
 **/


#pragma once
#include"CoreMinimal.h"
#include"Tools/VisualInterface.h"



/* ���ֶ����ʽ */
enum class CharactersPattern :uint8
{
	Left,
	Middle,
	Right
};

/* ���� */
namespace ArtyEngine
{
	class Characters
	{
		int32 row = 1;
		int32 maxWidth = 0;
		std::string texts = "";
		int size = 3;
		LPCTSTR style = "����";

		//��ɫӳ���
		static std::unordered_map<std::string, COLORREF> TextColorMap;
	public:
		int GetWidth() const { return maxWidth; }
		int GetHeight() const { return row * size * 6; }

		void SetCharacters(std::string text, int size = 3, LPCTSTR style = "����");
		void PrintCharacters(FVector2D pos, BYTE alpha = 255, CharactersPattern pattern = CharactersPattern::Middle);
	};
}





/* ��������ģʽ */
enum class LayoutPattern :uint8
{
	LeftTop,
	MiddleTop,
	RightTop,
	LeftMiddle,
	Center,
	RightMiddle,
	LeftBottom,
	MiddleBottom,
	RightBottom
};

/* ���������� */
enum class UIPattern :uint8
{
	None,
	VisibleOnly,
	VisibleAndInteractive
};

/*----------------------------------
			  ����С����
  ----------------------------------*/
class Widget :public Object, public LayerInterface
{
	friend class Panel;
	FIntVector2 point{ -1, -1 }, point_1{ -1, -1 };

	void BeginPlay()override {}
	void EndPlay()override {}
	FVector2D GetLayoutOffset()const;//����ƫ��
protected:
	FTransform transform;
	Widget* parent = nullptr;
	std::unordered_set<Widget*>children;
	Panel* attachedPanel = nullptr;

	FVector2D size;

	LayoutPattern layoutPattern;
	UIPattern uiPattern;

	ArtyEngine::Characters InfoText;
	bool bInfoBox = false;
	bool IsUnderCursor() const;

public:
	Widget() : layoutPattern(LayoutPattern::LeftTop), uiPattern(UIPattern::None) {}
	virtual ~Widget();

	virtual void Update();
	virtual void Render() {}
	void ShowInfoBox();
	void DrawDebugRect();

	void SetLayoutPattern(LayoutPattern pattern) { layoutPattern = pattern; }
	void SetUIPattern(UIPattern pattern);
	UIPattern GetUIPattern()const { return uiPattern; }
	void EnableInfoBox(bool showInfo) { bInfoBox = showInfo; }
	void SetInfoText(std::string text) { InfoText.SetCharacters(text); }

	virtual FVector2D GetSize() const;
	void SetSize(FVector2D size) {this->size = size; }

	void AttachTo(Widget* par);
	void DetachFrom(Widget* par);

	FVector2D GetScreenPosition() const;
	float GetScreenRotation() const;
	FVector2D GetScreenScale() const;

	FVector2D GetRelativePosition() const { return transform.position;}
	float GetRelativeRotation() const { return transform.rotation; }
	FVector2D GetRelativeScale() const { return transform.scale; }

	void SetRelativePosition(FVector2D pos) { transform.position = pos; }
	void SetRelativeRotation(float angle) { transform.rotation = angle; }
	void SetRelativeScale(FVector2D scale) { transform.scale = scale; }
};





/*--------------------------------------------------------------------
			                   �������

  > ����С������UserInterface��������UserInterfaceʱ,���������ɻ��������� <
  --------------------------------------------------------------------*/
class Panel :public Widget
{
	void SetSize(FVector2D size) { this->size = size; }//�������ֶ�����Panel�Ĵ�С
protected:
	std::vector<class Widget*>members;
	std::vector<class UserInterface*>members_ui;

	FVector2D unitSize;
	virtual void AdjustMemberPosition(Widget* member, int32 index) = 0;
public:
	virtual ~Panel();

	virtual void Update()override;

	void SetUnitSize(FVector2D size);

	void AddMember(Widget* member, int32 index = -1);
	void RemoveMember(Widget* member);

	void AddMember(UserInterface* member, int32 index = -1);
	void RemoveMember(UserInterface* member);

private:
	void AdjustMemberSizeToUnit(Widget* member);
};

/*----------------------------------
			  ˮƽ���
  ----------------------------------*/
class HorizontalPanel final :public Panel
{
	float spacing = 0;
	void AdjustMemberPosition(Widget* member, int32 index)override;
public:
	void SetSpacing(float space) { spacing = space; }
	FVector2D GetSize() const override;
};

/*----------------------------------
			  ��ֱ���
  ----------------------------------*/
class VerticalPanel final :public Panel
{
	float spacing = 0;
	void AdjustMemberPosition(Widget* member, int32 index)override;
public:
	void SetSpacing(float space) { spacing = space; }
	FVector2D GetSize() const override;
};

/*----------------------------------
			  �������
  ----------------------------------*/
class GridPanel final :public Panel
{
	int32 row = 1;
	int32 column = 1;
	float spacingX = 0;
	float spacingY = 0;
	void AdjustMemberPosition(Widget* member, int32 index)override;
public:
	void SetRow(int32 num) { row = num; }
	void SetColumn(int32 num) { column = num; }
	void SetSpacingX(float space) { spacingX = space; }
	void SetSpacingY(float space) { spacingY = space; }
	FVector2D GetSize() const override;
};





/*----------------------------------
			  �ı�����
  ----------------------------------*/
class Text :public Widget
{
protected:
	ArtyEngine::Characters texts;
	CharactersPattern textPattern;
	std::string* bindedText = nullptr;
	BYTE alpha = 255;
public:
	Text() :textPattern(CharactersPattern::Middle) {}

	virtual void Update();

	virtual void Render()override;

	void SetPattern(CharactersPattern pattern) { textPattern = pattern; }
	BYTE GetAlpha()const { return alpha; }
	void SetAlpha(BYTE alpha);
	void SetText(std::string te, int si = 3, LPCTSTR st = "����") { texts.SetCharacters(te, si, st); }
	void BindText(std::string& origin) { bindedText = &origin; }
};





class Animator;

/*----------------------------------
			  ͼ�񲿼�
  ----------------------------------*/
class Image :public Widget, public ImageInterface
{
	void DealImage()override;

public:
	virtual ~Image();
	virtual void Update()override;
	virtual void Render()override;

	bool IsMouseOn();

	IMAGE* LoadSprite(std::string name);

	//������������
	void EnableAnimControl();

	//��ȡ����������
	Animator* GetAnimator() { return ani; }

private:
	Animator* ani;
};





/* ��ťί�� */
DECLARE_NO_PARAM_MULTICAST_DELEGATE_CLASS(ButtonDelegate)

/*----------------------------------
			  ��ť����
  ----------------------------------*/
class Button final :public Image
{
	IMAGE* normal{};
	IMAGE* hover{};
	IMAGE* pressed{};

	bool isPressed = false;
	bool isHover = false;

public:
	virtual void Update()override;

	void LoadNormalPicture(std::string path);
	void LoadHoverPicture(std::string path);
	void LoadClickPicture(std::string path);

	bool IsMousePressed();

	ButtonDelegate OnMousePressedBegin;
	ButtonDelegate OnMousePressedEnd;
	ButtonDelegate OnMouseHoverBegin;
	ButtonDelegate OnMouseHoverEnd;
};






/* �������������� */
enum class BarDirection :uint8
{
	RightToLeft,
	LeftToRight,
	TopToBottom,
	BottomToTop
};

/*----------------------------------
			  ����������
  ----------------------------------*/
class Bar final :public Widget
{
	float percentage = 0;
	IMAGE* barFront{};
	IMAGE* barBack{};
	IMAGE* barButton{};
	FIntVector2 sizeFront = FIntVector2(0, 0);
	FIntVector2 sizeBack = FIntVector2(0, 0);
	FIntVector2 sizeButton = FIntVector2(0, 0);
	BarDirection direction;
public:
	virtual void Update()override;
	virtual void Render()override;

	void LoadBarFrontPicture(std::string path);
	void LoadBarBackPicture(std::string path);
	void LoadBarButtonPicture(std::string path);

	void SetDirection(BarDirection dir) { direction = dir; }
	void SetFrontSize(FIntVector2 size) { sizeFront = size; }
	void SetBackSize(FIntVector2 size) { sizeBack = size; }
	void SetButtonSize(FIntVector2 size) { sizeButton = size; }

	void SetPercentage(float per);
	float GetPercentage() const { return percentage; }
};


/*----------------------------------
			  ���β���
  ----------------------------------*/
class Sector final :public Widget
{
	float percentage = 0;
	IMAGE* sectorFront;
	IMAGE* sectorBack;
	FIntVector2 sizeFront = FIntVector2(0, 0);
	FIntVector2 sizeBack = FIntVector2(0, 0);
	float startDegree = 90;
public:
	virtual void Update()override;
	virtual void Render()override;

	void LoadSectorFrontPicture(std::string path);
	void LoadSectorBackPicture(std::string path);

	void SetFrontSize(FIntVector2 size) { sizeFront = size; }
	void SetBackSize(FIntVector2 size) { sizeBack = size; }

	void SetPercentage(float per);
	float GetPercentage() const { return percentage; }

	void SetStartDegree(float start);
};