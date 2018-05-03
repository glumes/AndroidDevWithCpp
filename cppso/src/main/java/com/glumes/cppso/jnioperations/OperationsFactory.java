package com.glumes.cppso.jnioperations;

import android.util.SparseArray;

import com.glumes.cppso.utils.ConstantsKt;
import com.glumes.cppso.utils.LogUtil;

/**
 * @Author glumes
 */
public class OperationsFactory {


    private SparseArray<BaseOperation> mOperations = new SparseArray<>();

    private static class OperationsFactoryHolder {
        private static OperationsFactory mInstance = new OperationsFactory();
    }

    private OperationsFactory() {

    }


    public static OperationsFactory getInstance() {
        return OperationsFactoryHolder.mInstance;
    }

    public BaseOperation getOperations(int type) {

        BaseOperation ops = mOperations.get(type);

        if (ops != null) {
            return ops;
        }

        switch (type) {
            case ConstantsKt.NATIVE_BASIC_TYPE:
                ops = new BasicTypeOps();
                break;
            case ConstantsKt.NATIVE_STRING:
                ops = new StringTypeOps();
                break;
            case ConstantsKt.NATIVE_ARRAY:
                ops = new ArrayTypeOps();
                break;
            case ConstantsKt.NATIVE_FIELD_AND_METHOD:
                ops = new FieldAndMethodOps();
                break;
            case ConstantsKt.NATIVE_CACHE_FIELD_AND_METHOD:
                ops = new CacheFieldAndMethodOps();
                break;
            case ConstantsKt.NATIVE_INVOKE_CONSTRUCTORS:
                ops = new InvokeConstructorOps();
                break;
            default:
                break;
        }

        if (ops != null) {
            mOperations.put(type, ops);
            return mOperations.get(type);
        }

        // default operations
        return new NoOperation();

    }
}
