
���ǡ�Qt 5.9 C++����ָ�ϡ�һ������ʵ��������Դ���룬ȫ��ʵ����������Qt 5.12.1 ����Ͳ��ԣ�����Qt 5.12.1�б����д���Ľ������޸ġ��޸ĺ󼸺�����ʵ�����������Qt 5.12.1���������С�

��ע�⣺Qt Creator����Ŀʱ����Ŀ·���в����к��ֻ�ȫ�Ƿ��ţ������޷����롿

�������ڣ�2019��5��
�������Ի�����64λWindow 7ϵͳ , Qt 5.12.1


��Qt 5.9 C++����ָ�ϡ�ͼ����Ϣ��

���ߣ���ά���������飬���

�����ʵ�����磬2018��5�³���


��1���󲿷ֳ��򶼿�����Qt 5.12.1��ֱ�ӱ�������У�ֻ������ʵ���д���

(1)ԭ����ʵ��samp8_2 ���������⣬paintEvent()�Ĵ�������ʾstd::cos(), std::sin()���������ڡ���Ϊʹ��<Qtmath>�еĺ���qSin()��qCos()���޸ĺ�ɱ����ˡ�

(2)samp12_4����Delphi��д��ʵ���޷����У���ΪDelphi��32λ�ģ���д��DLL��32λ�ģ���Qt 5.12.1��minGW��MSVC����������64λ�ġ���Qt 5.13��������32λ��������ʹ��32λ�������Ϳ��ԡ�


��2����12�±�дQt Creator���� Qt Designer�Ĳ������Ҫʹ�� MSVC 2015 32bit������������Qt 5.12.1�Ժ�ȡ��������������汾�� ��Qt Creator������MSVC 2015 32bit����ģ����ԣ���д�Ĳ���޷���Qt Creator���õ�Qt Designer����ʾ�����ǲ�Ӱ������ʹ�á�


��3��ʹ��QChart�ĳ����У�������ʾ��Щ������ʱ�����޸�Ҳ��Ӱ���������У��漰���¼���ʵ����

(1)ʵ��samp9_2������ʱ��ʾQChart::setAxisX(), QChart::setAxisY()������ʱ,Ӧ��Ϊ����ķ�ʽ���������
    chart->addAxis(axisX,Qt::AlignBottom); //��������ӵ�ͼ����ָ������
    chart->addAxis(axisY,Qt::AlignLeft);

    series0->attachAxis(axisX); //���� series0 ����������
    series0->attachAxis(axisY);

    series1->attachAxis(axisX); //���� series1 ����������
    series1->attachAxis(axisY);

    ����ʱ��ʾQChart::axisX(), QChart::axisY()������ʱ�������޸�Ϊ���µ���ʽ��
    QList<QAbstractAxis*> axes;
    if (ui->radioX->isChecked())
        axes=ui->chartView->chart()->axes(Qt::Horizontal);
    else
        axes=ui->chartView->chart()->axes(Qt::Vertical);
    curAxis=(QValueAxis*)axes[0];

(2)ʵ��samp9_1������ʱ��ʾQChart::setAxisX(), QChart::setAxisY()������ʱ������Ȼ�ǿ���ʹ�õġ�Ϊ�������ϵ�����һ�£�δ���޸�

(3)ʵ��samp9_3������ʱ��ʾQChart::axisX(), QChart::axisY()������ʱ�������õ������������Ĵ���Ƚ϶࣬��δ���޸�

(4)samp15_4, �滻�˹�ʱ�ĺ���QChart::setAxisX(), QChart::setAxisY()

