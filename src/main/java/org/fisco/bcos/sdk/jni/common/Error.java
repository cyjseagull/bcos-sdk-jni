package org.fisco.bcos.sdk.jni.common;

public class Error {
  private int errorCode;
  private String errorMessage;

  public int getErrorCode() {
    return errorCode;
  }

  public void setErrorCode(int errorCode) {
    this.errorCode = errorCode;
  }

  public String getErrorMessage() {
    return errorMessage;
  }

  public void setErrorMessage(String errorMessage) {
    this.errorMessage = errorMessage;
  }

  @Override
  public String toString() {
    return "Error{" + "errorCode=" + errorCode + ", errorMessage='" + errorMessage + '\'' + '}';
  }
}
