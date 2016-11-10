import atexit

def bf_to_str(bf):
    import SCons.Errors
    if bf is None:
        return '(unknown target)'
    elif isinstance(bf, SCons.Errors.StopError):
        return str(bf)
    elif bf.node:
        return str(bf.node) + ': ' + bf.errstr
    elif bf.filename:
        return bf.filename + ': ' + bf.error
    return 'unknown failure: ' + bf.errstr

def build_status():
    from SCons.Script import GetBuildFailures
    bf = GetBuildFailures()
    if bf:
        status = 'failed'
        failures_messsage = "\n".join(["Failed building %s" % bf_to_str(x) for x in bf if x is not None])
    else:
        status = 'ok'
        failures_messsage = ''
    return (status, failures_messsage)