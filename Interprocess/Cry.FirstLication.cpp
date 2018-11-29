#include <Global>
#include <Cry.FirstLication.h>
#include <Injection/Message.h>
#include <InterProcess/Cry.Signal.Service.h>
#include <SendCmd.pb.h>
#include <StringXor.h>
namespace QWindows
{
	FirstLication::FirstLication(Cry::Signal::NetworkEngineService* Service, QWidget *Parent) : QWidget(Parent), m_Service(Service)
	{
		if (!m_Service->GetObjectInterface()->Add("FirstLication", this))
		{
			DebugMsg("����[%s]�Ѿ�����\n", "FirstLication");
		}
		this->SetupInterface(this);
	}

	FirstLication::~FirstLication()
	{

	}
	bool FirstLication::SetupInterface(QWidget *Parent)
	{
		uint32_t w = 0, h = 0;
		if (!QtWin::isCompositionEnabled())
		{
			w = 602;
			h = 400;
			DebugMsg("Aero:�ر�[%d] w:%d h:%d\n", reinterpret_cast<HWND>(this->winId()), w, h);
			QApplication::setStyle(QStyleFactory::create("Fusion"));
		}
		else
		{
			w = 600;
			h = 400;
			DebugMsg("Aero:����[%d] w:%d h:%d\n", reinterpret_cast<HWND>(this->winId()), w, h);
		}
		if (this->QWidget::objectName().isEmpty())
		{
			this->QWidget::setObjectName(QStringLiteral("Dialog"));
		}
		this->setWindowTitle(QString::fromLocal8Bit(_T("")));
		this->resize(w, h);
		this->setMaximumSize(QSize(w, h));
		this->setMinimumSize(QSize(w, h));
		this->setWindowFlags(this->windowFlags()& ~Qt::WindowMaximizeButtonHint);
		this->setFixedSize(QSize(w, h));
		try
		{
			(m_Tab = m_Pair.insert(������, new QTabWidget(Parent)))->setObjectName(QString::fromLocal8Bit(_T("�����ǩ")));
			(m_Widget[0] = m_Pair.insert(��������, new QWidget(m_Tab)))->setObjectName(QString::fromLocal8Bit(_T("��������")));
			(m_Widget[1] = m_Pair.insert(��������, new QWidget(m_Tab)))->setObjectName(QString::fromLocal8Bit(_T("��������")));
			/* ˮƽ���� Star*/
			(m_WidgetLayout = m_Pair.insert(ˮƽ���, new QWidget(m_Widget[0])))->setObjectName(QString::fromLocal8Bit(_T("ˮƽ���")));
			(m_HBoxLayout = m_Pair.insert(ˮƽ����, new QHBoxLayout(m_WidgetLayout)))->setObjectName(QString::fromLocal8Bit(_T("ˮƽ����")));
			(m_CheckBox[0] = m_Pair.insert(��������, new QCheckBox()))->setObjectName(QString::fromLocal8Bit(_T("��������")));
			(m_CheckBox[1] = m_Pair.insert(ħ������, new QCheckBox()))->setObjectName(QString::fromLocal8Bit(_T("ħ������")));
			(m_CheckBox[2] = m_Pair.insert(��������, new QCheckBox()))->setObjectName(QString::fromLocal8Bit(_T("��������")));
			/* ˮƽ���� End*/
			/* ���Բ��� Star*/
			(m_TestWidget = m_Pair.insert(���Կ��, new QWidget(m_Widget[0])))->setObjectName(QString::fromLocal8Bit(_T("���Կ��")));
			(m_TestLayout = m_Pair.insert(���Բ���, new QHBoxLayout(m_TestWidget)))->setObjectName(QString::fromLocal8Bit(_T("���Բ���")));
			(m_PushButton[0] = m_Pair.insert(ע����Ϣ, new QPushButton(m_TestWidget)))->setObjectName(QString::fromLocal8Bit(_T("ע����Ϣ")));
			(m_PushButton[1] = m_Pair.insert(ж����Ϣ, new QPushButton(m_TestWidget)))->setObjectName(QString::fromLocal8Bit(_T("ж����Ϣ")));
			(m_PushButton[2] = m_Pair.insert(������Ϣ, new QPushButton(m_TestWidget)))->setObjectName(QString::fromLocal8Bit(_T("������Ϣ")));
			{
				m_Tab->setGeometry(QRect(2, 2, 598, 397));
				m_Tab->addTab(m_Widget[0], QString::fromLocal8Bit(_T("��������")));
				m_Tab->addTab(m_Widget[1], QString::fromLocal8Bit(_T("��������")));
				m_Tab->setCurrentIndex(0);
				m_WidgetLayout->setGeometry(QRect(10, 10, 240, 20));
				m_HBoxLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
				m_HBoxLayout->setContentsMargins(0, 0, 0, 0);
				
				m_HBoxLayout->addWidget(m_CheckBox[0]);
				m_HBoxLayout->addWidget(m_CheckBox[1]);
				m_HBoxLayout->addWidget(m_CheckBox[2]);

				m_CheckBox[0]->setText(QString::fromLocal8Bit(_T("��������")));
				m_CheckBox[1]->setText(QString::fromLocal8Bit(_T("ħ������")));
				m_CheckBox[2]->setText(QString::fromLocal8Bit(_T("��������")));
				for (auto &Args : m_CheckBox)
				{
					Args->setStyle(QStyleFactory::create(_T("Fusion")));
				}
				m_TestWidget->setGeometry(QRect(320, 330, 250, 26));
				m_TestLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
				m_TestLayout->setContentsMargins(0, 0, 0, 0);

				m_TestLayout->addWidget(m_PushButton[0]);
				m_TestLayout->addWidget(m_PushButton[1]);
				m_TestLayout->addWidget(m_PushButton[2]);

				m_PushButton[0]->setText(QString::fromLocal8Bit(_T("ע����Ϣ")));
				m_PushButton[1]->setText(QString::fromLocal8Bit(_T("ж����Ϣ")));
				m_PushButton[2]->setText(QString::fromLocal8Bit(_T("������Ϣ")));

				for (auto &Args : m_PushButton)
				{
					Args->setStyle(QStyleFactory::create(_T("Fusion")));
				}
				
				QObject::connect(m_PushButton[0], &QPushButton::clicked, this, &FirstLication::OnInjection);
				QObject::connect(m_PushButton[1], &QPushButton::clicked, this, &FirstLication::OnUninstall);
				QObject::connect(m_PushButton[2], &QPushButton::clicked, this, &FirstLication::OnSend);

				/*
				1��Qt::AutoConnection�� Ĭ��ֵ��ʹ�����ֵ���������ͻ����źŷ���ʱ��������������ߺͷ�������ͬһ���̣߳����Զ�ʹ��Qt::DirectConnection���͡���������ߺͷ����߲���һ���̣߳����Զ�ʹ��Qt::QueuedConnection���͡�
				2��Qt::DirectConnection���ۺ��������źŷ��͵�ʱ��ֱ�ӱ����ã��ۺ����������źŷ����������̡߳�Ч������ȥ������ֱ�����źŷ���λ�õ����˲ۺ���������ڶ��̻߳����±Ƚ�Σ�գ����ܻ���ɱ�����
				3��Qt::QueuedConnection���ۺ����ڿ��ƻص������������̵߳��¼�ѭ��ʱ�����ã��ۺ����������źŽ����������̡߳������ź�֮�󣬲ۺ����������̱����ã��ȵ������ߵĵ�ǰ����ִ���꣬�����¼�ѭ��֮�󣬲ۺ����Żᱻ���á����̻߳�����һ���������
				4��Qt::BlockingQueuedConnection���ۺ����ĵ���ʱ����Qt::QueuedConnectionһ�£������������źź����������̻߳�������ֱ���ۺ��������ꡣ�����ߺͷ����߾��Բ�����һ���̣߳����������������ڶ��̼߳���Ҫͬ���ĳ��Ͽ�����Ҫ�����
				5��Qt::UniqueConnection�����flag����ͨ����λ��|���������ĸ������һ��ʹ�á������flag����ʱ����ĳ���źźͲ��Ѿ�����ʱ���ٽ����ظ������Ӿͻ�ʧ�ܡ�Ҳ���Ǳ������ظ����ӡ�
				*/

				QObject::connect(this, &FirstLication::SendNotify, this, &FirstLication::OnNotify, Qt::BlockingQueuedConnection);

				QObject::connect(this, &FirstLication::PostNotify, m_Service, &Cry::Signal::NetworkEngineService::OnNotify, Qt::AutoConnection);
			}
			QMetaObject::connectSlotsByName(this);
		}
		catch (std::string e)
		{
			DebugMsg(e.c_str());
		}
		return true;
	}
	bool FirstLication::OnSocketData(const std::shared_ptr<Cry::Signal::Work> & pWork, const uint32_t uMsg, const void * pData, const uint32_t uSize)
	{
		return emit SendNotify(uMsg, pData, uSize);
	}
	bool FirstLication::OnNotify(const uint32_t uMsg, const void * pData, const uint32_t uSize)
	{
		SocketData::CmdResponse Resp;
		if (!Resp.ParsePartialFromArray(pData, uSize))
		{
			return false;
		}
		if (Resp.status())
		{
			this->setWindowTitle(QString::fromLocal8Bit("�ͻ��˷�����ȷ"));
		}
		else
		{
			this->setWindowTitle(QString::fromLocal8Bit("�ͻ��˷��ش���"));
		}
		return false;
	}
	void FirstLication::OnInjection()
	{
		if (Cry::Kernel::Message::InstallWindowsMessageEx(FindWindow("TApplication", "Legend of Mir2"), TEXT("./Library.dll"), TEXT("InterFaceDll")))
		{
			DebugMsg("��װ�ɹ�\n");
		}
	}
	void FirstLication::OnUninstall()
	{
		if (PostMessage(FindWindow("TApplication", "Legend of Mir2"), WM_USER + 9999, 9527, 1))
		{
			if (!SleepEx(30, TRUE))
			{
				if (Cry::Kernel::Message::UninstallWindowsMessageEx())
				{
					DebugMsg("ж�سɹ�\n");
				}
			}
		}
	}
	void FirstLication::OnSend()
	{
		DebugMsg("����:%s\n", Cry::Text::Xor::Operate("\x58\xFF\x40\xF9\x53\x9D\x25\x85\x40\x82\x5F\x9D\x5F\x82\x40\x82\x5F\x9D\x5F\x82\x40\x85\x54\x9D\x23\x8D\x40\x8A\x54\x9D\x5F\x82\x40\x85\x50\x9D\x22\xFF\x40\x82\x5F\x9D\x5F\x82\x40\x82\x5F\x9D\x5F\x82\x40\x8D\x50\x00\x00").c_str());
		SocketData::CmdRequest Req;
		Req.clear_content();
		Req.set_content("123321123321");
		if (!emit PostNotify(0, Req))
		{
			DebugMsg("����ʧ��\n");
		}
	}
}