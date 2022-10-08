
#ifndef SQUICK_RECORD_H
#define SQUICK_RECORD_H

#include <vector>
#include "i_record.h"
#include "data_list.h"
#include "map_ex.h"
#include "platform.h"

class _SquickExport Record : public IRecord
{
public:
    Record();
    Record(const Guid& self, const std::string& recordName, const SQUICK_SHARE_PTR<DataList>& valueList, const SQUICK_SHARE_PTR<DataList>& tagList, const int nMaxRow);

    virtual ~Record();

    virtual std::string ToString();
	virtual void ToMemoryCounterString(std::string& data);

    virtual bool IsUsed(const int row) const;

    virtual bool SetUsed(const int row, const int bUse);

	virtual bool PreAllocMemoryForRow(const int row);

    virtual int GetCols() const;

    virtual int GetRows() const;
	virtual int GetUsedRows() const;

    virtual DATA_TYPE GetColType(const int col) const;
    virtual const std::string& GetColTag(const int col) const;

    
    virtual int AddRow(const int row);

	virtual int AddRow(const int row, const DataList& var);

	virtual bool SetRow(const int row, const DataList& var);

    virtual bool SetInt(const int row, const int col, const INT64 value);
    virtual bool SetFloat(const int row, const int col, const double value);
    virtual bool SetString(const int row, const int col, const std::string& value);
    virtual bool SetObject(const int row, const int col, const Guid& value);
	virtual bool SetVector2(const int row, const int col, const Vector2& value);
	virtual bool SetVector3(const int row, const int col, const Vector3& value);

    virtual bool SetInt(const int row, const std::string& colTag, const INT64 value);
    virtual bool SetFloat(const int row, const std::string& colTag, const double value);
    virtual bool SetString(const int row, const std::string& colTag, const std::string& value);
    virtual bool SetObject(const int row, const std::string& colTag, const Guid& value);
	virtual bool SetVector2(const int row, const std::string& colTag, const Vector2& value);
	virtual bool SetVector3(const int row, const std::string& colTag, const Vector3& value);

    virtual bool QueryRow(const int row, DataList& varList);

    virtual bool SwapRowInfo(const int nOriginRow, const int nTargetRow);

    virtual INT64 GetInt(const int row, const int col) const;
    virtual double GetFloat(const int row, const int col) const;
    virtual const std::string& GetString(const int row, const int col) const;
    virtual const Guid& GetObject(const int row, const int col) const;
	virtual const Vector2& GetVector2(const int row, const int col) const;
	virtual const Vector3& GetVector3(const int row, const int col) const;

    virtual INT64 GetInt(const int row, const std::string& colTag) const;
    virtual double GetFloat(const int row, const std::string& colTag) const;
    virtual const std::string& GetString(const int row, const std::string& colTag) const;
    virtual const Guid& GetObject(const int row, const std::string& colTag) const;
	virtual const Vector2& GetVector2(const int row, const std::string& colTag) const;
	virtual const Vector3& GetVector3(const int row, const std::string& colTag) const;

    virtual int FindRowByColValue(const int col, const SquickData& var, DataList& varResult);
    virtual int FindInt(const int col, const INT64 value, DataList& varResult);
    virtual int FindFloat(const int col, const double value, DataList& varResult);
	virtual int FindString(const int col, const std::string& value, DataList& varResult);
    virtual int FindObject(const int col, const Guid& value, DataList& varResult);
	virtual int FindVector2At(const int col, const Vector2& value, DataList& varResult);
	virtual int FindVector3At(const int col, const Vector3& value, DataList& varResult);

	virtual int FindRowByColValue(const int col, const SquickData& var);
	virtual int FindInt(const int col, const INT64 value);
	virtual int FindFloat(const int col, const double value);
	virtual int FindString(const int col, const std::string& valuet);
	virtual int FindObject(const int col, const Guid& value);
	virtual int FindVector2At(const int col, const Vector2& value);
	virtual int FindVector3At(const int col, const Vector3& value);

    virtual int FindRowByColValue(const std::string& colTag, const SquickData& var, DataList& varResult);
    virtual int FindInt(const std::string& colTag, const INT64 value, DataList& varResult);
    virtual int FindFloat(const std::string& colTag, const double value, DataList& varResult);
	virtual int FindString(const std::string& colTag, const std::string& value, DataList& varResult);
    virtual int FindObject(const std::string& colTag, const Guid& value, DataList& varResult);
	virtual int FindVector2At(const std::string& colTag, const Vector2& value, DataList& varResult);
	virtual int FindVector3At(const std::string& colTag, const Vector3& value, DataList& varResult);

	virtual int FindRowByColValue(const std::string& colTag, const SquickData& var);
	virtual int FindInt(const std::string& colTag, const INT64 value);
	virtual int FindFloat(const std::string& colTag, const double value);
	virtual int FindString(const std::string& colTag, const std::string& value);
	virtual int FindObject(const std::string& colTag, const Guid& value);
	virtual int FindVector2At(const std::string& colTag, const Vector2& value);
	virtual int FindVector3At(const std::string& colTag, const Vector3& value);

    virtual bool Remove(const int row);

    virtual bool Clear();

    virtual void AddRecordHook(const RECORD_EVENT_FUNCTOR_PTR& cb);

    virtual const bool GetSave();

    virtual const bool GetCache();

	virtual const bool GetRef();

	virtual const bool GetForce();

	virtual const bool GetUpload();

    virtual const bool GetPublic();

    virtual const bool GetPrivate();

    virtual const std::string& GetName() const;

    virtual void SetSave(const bool bSave);

	virtual void SetCache(const bool bCache);

	virtual void SetRef(const bool bRef);

	virtual void SetForce(const bool bForce);

	virtual void SetUpload(const bool bUpload);

    virtual void SetPublic(const bool bPublic);

    virtual void SetPrivate(const bool bPrivate);

    virtual void SetName(const std::string& name);

    virtual SQUICK_SHARE_PTR<DataList> GetInitData() const;
    virtual const SQUICK_SHARE_PTR<DataList> GetTag() const;

    virtual const TRECORDVEC& GetRecordVec() const;
protected:
    int GetPos(int row, int col) const;

    int GetCol(const std::string& strTag) const;

    bool ValidPos(int row, int col) const;
    bool ValidRow(int row) const;
    bool ValidCol(int col) const;

    void OnEventHandler(const Guid& self, const RECORD_EVENT_DATA& eventData, const SquickData& oldVar, const SquickData& newVar);

protected:
    
	SQUICK_SHARE_PTR<DataList> mVarRecordType;
	SQUICK_SHARE_PTR<DataList> mVarRecordTag;

    std::map<std::string, int> mmTag;

	////////////////////////////

	//TODO
	struct RowData
	{

	};

	std::vector<RowData> mRecordData;

	TRECORDVEC mtRecordVec;
	std::vector<int> mVecUsedState;
    int mnMaxRow;

    Guid mSelf;
    bool mbSave;
    bool mbPublic;
    bool mbPrivate;
	bool mbCache;
	bool mbRef;
	bool mbForce;
	bool mbUpload;
    std::string mstrRecordName;

    typedef std::vector<RECORD_EVENT_FUNCTOR_PTR> TRECORDCALLBACKEX;
    TRECORDCALLBACKEX mtRecordCallback;
};

#endif
