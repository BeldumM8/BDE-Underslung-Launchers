class BDE_USL_Client40mmFireContext
{
    Object m_Source;
    string m_AmmoType;
    vector m_MuzzlePosition;
    vector m_ShotDirection;
    int m_ShotId;
    int m_CreatedAt;

    void BDE_USL_Client40mmFireContext(Object source, string ammoType, vector muzzlePosition, vector shotDirection, int shotId, int createdAt)
    {
        m_Source = source;
        m_AmmoType = ammoType;
        m_MuzzlePosition = muzzlePosition;
        m_ShotDirection = shotDirection;
        m_ShotId = shotId;
        m_CreatedAt = createdAt;
    }
}

class BDE_USL_40mmShotContext
{
    Object m_Source;
    Object m_FallbackDamageSource;
    string m_AmmoType;
    vector m_ProjectilePosition;
    vector m_ShotDirection;
    vector m_InheritedVelocity;
    float m_LaunchSpeed;
    vector m_WatchPosition;
    vector m_WatchVelocity;
    int m_WatchLastTickAt;
    bool m_WatchActive;
    int m_ShotId;
    int m_CreatedAt;
    bool m_FireResultKnown;
    bool m_FireResult;
    bool m_TerminalEffectHandled;
    bool m_TerminalFallbackQueued;
    int m_PhysicalAttempts;

    void BDE_USL_40mmShotContext(Object source, string ammoType, vector projectilePosition, vector shotDirection, vector inheritedVelocity, float launchSpeed, int shotId, int createdAt)
    {
        m_Source = source;
        m_AmmoType = ammoType;
        m_ProjectilePosition = projectilePosition;
        m_ShotDirection = shotDirection;
        m_InheritedVelocity = inheritedVelocity;
        m_LaunchSpeed = launchSpeed;
        m_WatchPosition = projectilePosition;
        m_WatchVelocity = (shotDirection * launchSpeed) + inheritedVelocity;
        m_WatchLastTickAt = createdAt;
        m_WatchActive = false;
        m_ShotId = shotId;
        m_CreatedAt = createdAt;
        m_FireResultKnown = false;
        m_FireResult = false;
        m_TerminalEffectHandled = false;
        m_TerminalFallbackQueued = false;
        m_PhysicalAttempts = 1;

        EntityAI sourceEntity = EntityAI.Cast(source);

        if (sourceEntity)
            m_FallbackDamageSource = sourceEntity.GetHierarchyParent();
    }
}

class BDE_USL_Six12ShotContext
{
    Object m_Source;
    Object m_Host;
    string m_AmmoType;
    vector m_ProjectilePosition;
    vector m_ShotDirection;
    vector m_InheritedVelocity;
    float m_LaunchSpeed;
    vector m_WatchPosition;
    vector m_WatchVelocity;
    int m_WatchLastTickAt;
    bool m_WatchActive;
    int m_ShotId;
    int m_CreatedAt;
    bool m_FireResultKnown;
    bool m_FireResult;
    bool m_EngineImpactObserved;
    bool m_FallbackQueued;
    int m_PredictedImpactAt;
    string m_PredictedReason;

    void BDE_USL_Six12ShotContext(Object source, Object host, string ammoType, vector projectilePosition, vector shotDirection, vector inheritedVelocity, float launchSpeed, int shotId, int createdAt)
    {
        m_Source = source;
        m_Host = host;
        m_AmmoType = ammoType;
        m_ProjectilePosition = projectilePosition;
        m_ShotDirection = shotDirection;
        m_InheritedVelocity = inheritedVelocity;
        m_LaunchSpeed = launchSpeed;
        m_WatchPosition = projectilePosition;
        m_WatchVelocity = (shotDirection * launchSpeed) + inheritedVelocity;
        m_WatchLastTickAt = createdAt;
        m_WatchActive = false;
        m_ShotId = shotId;
        m_CreatedAt = createdAt;
        m_FireResultKnown = false;
        m_FireResult = false;
        m_EngineImpactObserved = false;
        m_FallbackQueued = false;
        m_PredictedImpactAt = -1;
        m_PredictedReason = "none";
    }
}

// Shared 3_Game <-> 4_World protection bridge. No Ninjins types here.
// 4_World handlers receive and update this query synchronously.
class BDE_USL_ZoneImpactQuery
{
    Object m_Target;
    vector m_Position;
    bool m_Explosion;
    bool m_Blocked;

    void BDE_USL_ZoneImpactQuery(Object target, vector position, bool explosion)
    {
        m_Target = target;
        m_Position = position;
        m_Explosion = explosion;
        m_Blocked = false;
    }
}

class BDE_USL_ZoneImpactRouter
{
    protected static ref ScriptInvoker s_ProtectionCheck;

    static ScriptInvoker GetProtectionCheck()
    {
        if (!s_ProtectionCheck)
            s_ProtectionCheck = new ScriptInvoker();
        return s_ProtectionCheck;
    }
}

modded class DayZGame
{
    protected ref array<ref BDE_USL_Client40mmFireContext> m_BDE_USL_Client40mmFireContexts;
    protected ref array<ref BDE_USL_40mmShotContext> m_BDE_USL_40mmShotContexts;
    protected ref array<ref BDE_USL_Six12ShotContext> m_BDE_USL_Six12ShotContexts;

    // The game layer cannot reference 4_World/Ninjins types. Zone handlers
    // register via BDE_USL_ZoneImpactRouter from 5_Mission at startup.
    bool BDE_USL_IsProtectedImpact(Object target, vector position, bool explosion)
    {
        EntityAI entity = EntityAI.Cast(target);
        if (entity && !entity.GetAllowDamage())
            return true;

        BDE_USL_ZoneImpactQuery query = new BDE_USL_ZoneImpactQuery(target, position, explosion);
        BDE_USL_ZoneImpactRouter.GetProtectionCheck().Invoke(query);
        return query.m_Blocked;
    }

    protected bool BDE_USL_IsTerminalPayload40mmAmmo(string ammoType)
    {
        return ammoType == "Bullet_40mm_Explosive" || ammoType == "Bullet_VOG25" || ammoType == "Bullet_40mm_ChemGas";
    }

    protected void BDE_USL_Prune40mmShotContexts()
    {
        if (!m_BDE_USL_40mmShotContexts)
            return;

        int now = GetGame().GetTime();

        for (int i = m_BDE_USL_40mmShotContexts.Count() - 1; i >= 0; i--)
        {
            BDE_USL_40mmShotContext context = m_BDE_USL_40mmShotContexts.Get(i);

            if (!context || now - context.m_CreatedAt > 45000)
                m_BDE_USL_40mmShotContexts.Remove(i);
        }
    }

    protected BDE_USL_40mmShotContext BDE_USL_Find40mmShotByIdentity(int shotId, Object source, string ammoType)
    {
        if (!m_BDE_USL_40mmShotContexts)
            return null;

        for (int i = m_BDE_USL_40mmShotContexts.Count() - 1; i >= 0; i--)
        {
            BDE_USL_40mmShotContext context = m_BDE_USL_40mmShotContexts.Get(i);

            if (!context || context.m_ShotId != shotId)
                continue;

            if (source && context.m_Source != source)
                continue;

            if (ammoType != "" && context.m_AmmoType != ammoType)
                continue;

            return context;
        }

        return null;
    }

    protected BDE_USL_40mmShotContext BDE_USL_FindBest40mmShot(string ammoType, Object engineSource, vector callbackPosition, vector inSpeed)
    {
        if (!m_BDE_USL_40mmShotContexts)
            return null;

        BDE_USL_Prune40mmShotContexts();
        int now = GetGame().GetTime();
        BDE_USL_40mmShotContext bestContext = null;
        float bestScore = -1000.0;

        for (int i = m_BDE_USL_40mmShotContexts.Count() - 1; i >= 0; i--)
        {
            BDE_USL_40mmShotContext context = m_BDE_USL_40mmShotContexts.Get(i);

            if (!context || context.m_AmmoType != ammoType)
                continue;

            if (context.m_FireResultKnown && !context.m_FireResult)
                continue;

            int age = now - context.m_CreatedAt;

            if (age < 0 || age > 45000)
                continue;

            if (engineSource && context.m_Source && engineSource != context.m_Source)
                continue;

            vector flatShot = Vector(context.m_ShotDirection[0], 0, context.m_ShotDirection[2]);
            vector flatTravel = callbackPosition - context.m_ProjectilePosition;
            flatTravel[1] = 0;
            vector flatImpactVelocity = Vector(inSpeed[0], 0, inSpeed[2]);

            float routeDot = 1.0;
            float velocityDot = 1.0;

            if (flatShot.Length() > 0.001 && flatTravel.Length() > 0.001)
                routeDot = vector.Dot(flatShot.Normalized(), flatTravel.Normalized());

            if (flatShot.Length() > 0.001 && flatImpactVelocity.Length() > 0.001)
                velocityDot = vector.Dot(flatShot.Normalized(), flatImpactVelocity.Normalized());

            if (routeDot < 0.25)
                continue;

            float score = (routeDot * 2.0) + (velocityDot * 0.5) - (age * 0.00001);

            if (score > bestScore)
            {
                bestScore = score;
                bestContext = context;
            }
        }

        return bestContext;
    }

    void BDE_USL_RegisterTerminal40mmShot(Object source, string ammoType, vector projectilePosition, vector shotDirection, vector inheritedVelocity, float launchSpeed, int shotId)
    {
        if (!source || !BDE_USL_IsTerminalPayload40mmAmmo(ammoType))
            return;

        if (!m_BDE_USL_40mmShotContexts)
            m_BDE_USL_40mmShotContexts = new array<ref BDE_USL_40mmShotContext>;

        BDE_USL_Prune40mmShotContexts();
        m_BDE_USL_40mmShotContexts.Insert(new BDE_USL_40mmShotContext(source, ammoType, projectilePosition, shotDirection, inheritedVelocity, launchSpeed, shotId, GetGame().GetTime()));
    }

    void BDE_USL_MarkTerminal40mmFireResult(int shotId, Object source, string ammoType, bool fired)
    {
        BDE_USL_40mmShotContext context = BDE_USL_Find40mmShotByIdentity(shotId, source, ammoType);

        if (!context)
            return;

        context.m_FireResultKnown = true;
        context.m_FireResult = fired;

        if (fired && IsServer())
            BDE_USL_StartTerminalWatchdog(context);
    }

    void BDE_USL_CancelTerminal40mmShot(int shotId, Object source, string ammoType)
    {
        if (!m_BDE_USL_40mmShotContexts)
            return;

        for (int i = m_BDE_USL_40mmShotContexts.Count() - 1; i >= 0; i--)
        {
            BDE_USL_40mmShotContext context = m_BDE_USL_40mmShotContexts.Get(i);

            if (!context || context.m_ShotId != shotId)
                continue;

            if (source && context.m_Source != source)
                continue;

            if (ammoType != "" && context.m_AmmoType != ammoType)
                continue;

            m_BDE_USL_40mmShotContexts.Remove(i);
            return;
        }
    }

    void BDE_USL_RegisterClient40mmFireSource(Object source, string ammoType, vector muzzlePosition, vector shotDirection, int shotId)
    {
        if (IsServer() || !source || !BDE_USL_IsTerminalPayload40mmAmmo(ammoType))
            return;

        if (!m_BDE_USL_Client40mmFireContexts)
            m_BDE_USL_Client40mmFireContexts = new array<ref BDE_USL_Client40mmFireContext>;

        int now = GetGame().GetTime();

        for (int i = m_BDE_USL_Client40mmFireContexts.Count() - 1; i >= 0; i--)
        {
            BDE_USL_Client40mmFireContext oldContext = m_BDE_USL_Client40mmFireContexts.Get(i);

            if (!oldContext || now - oldContext.m_CreatedAt > 15000)
                m_BDE_USL_Client40mmFireContexts.Remove(i);
        }

        m_BDE_USL_Client40mmFireContexts.Insert(new BDE_USL_Client40mmFireContext(source, ammoType, muzzlePosition, shotDirection, shotId, now));
    }

    void BDE_USL_CancelClient40mmFireSource(int shotId)
    {
        if (!m_BDE_USL_Client40mmFireContexts)
            return;

        for (int i = m_BDE_USL_Client40mmFireContexts.Count() - 1; i >= 0; i--)
        {
            BDE_USL_Client40mmFireContext context = m_BDE_USL_Client40mmFireContexts.Get(i);

            if (context && context.m_ShotId == shotId)
            {
                m_BDE_USL_Client40mmFireContexts.Remove(i);
                return;
            }
        }
    }

    protected Object BDE_USL_ResolveClient40mmFireSource(string ammoType, vector impactPosition, vector inSpeed, out int shotId)
    {
        shotId = -1;

        if (IsServer() || !m_BDE_USL_Client40mmFireContexts || m_BDE_USL_Client40mmFireContexts.Count() == 0)
            return null;

        int now = GetGame().GetTime();
        BDE_USL_Client40mmFireContext bestContext = null;
        float bestScore = -1000.0;

        for (int i = m_BDE_USL_Client40mmFireContexts.Count() - 1; i >= 0; i--)
        {
            BDE_USL_Client40mmFireContext context = m_BDE_USL_Client40mmFireContexts.Get(i);

            if (!context)
            {
                m_BDE_USL_Client40mmFireContexts.Remove(i);
                continue;
            }

            int age = now - context.m_CreatedAt;

            if (age < 0 || age > 15000)
            {
                m_BDE_USL_Client40mmFireContexts.Remove(i);
                continue;
            }

            if (!context.m_Source || context.m_AmmoType != ammoType)
                continue;

            vector flatShot = Vector(context.m_ShotDirection[0], 0, context.m_ShotDirection[2]);
            vector flatTravel = impactPosition - context.m_MuzzlePosition;
            flatTravel[1] = 0;
            vector flatImpactVelocity = Vector(inSpeed[0], 0, inSpeed[2]);

            float routeDot = 1.0;
            float velocityDot = 1.0;

            if (flatShot.Length() > 0.001 && flatTravel.Length() > 0.001)
                routeDot = vector.Dot(flatShot.Normalized(), flatTravel.Normalized());

            if (flatShot.Length() > 0.001 && flatImpactVelocity.Length() > 0.001)
                velocityDot = vector.Dot(flatShot.Normalized(), flatImpactVelocity.Normalized());

            if (routeDot < 0.45 || velocityDot < 0.25)
                continue;

            float score = (routeDot * 2.0) + velocityDot - (age * 0.00001);

            if (score > bestScore)
            {
                bestScore = score;
                bestContext = context;
            }
        }

        if (!bestContext || !bestContext.m_Source)
            return null;

        Object resolvedSource = bestContext.m_Source;
        shotId = bestContext.m_ShotId;
        int resolvedIndex = m_BDE_USL_Client40mmFireContexts.Find(bestContext);

        if (resolvedIndex >= 0)
            m_BDE_USL_Client40mmFireContexts.Remove(resolvedIndex);

        return resolvedSource;
    }

    protected Object BDE_USL_ResolveServer40mmFireSource(string ammoType, vector impactPosition, vector inSpeed, out int shotId)
    {
        shotId = -1;

        if (!IsServer() || !BDE_USL_IsTerminalPayload40mmAmmo(ammoType))
            return null;

        BDE_USL_40mmShotContext context = BDE_USL_FindBest40mmShot(ammoType, null, impactPosition, inSpeed);

        if (!context || !context.m_Source)
            return null;

        shotId = context.m_ShotId;
        return context.m_Source;
    }

    protected bool BDE_USL_IsSix12ProjectileAmmo(string ammoType)
    {
        return ammoType == "Bullet_12GaugePellets" || ammoType == "Bullet_12GaugeSlug" || ammoType == "Bullet_12GaugeRubberSlug" || ammoType == "Bullet_12GaugeBeanbag";
    }

    protected void BDE_USL_PruneSix12ShotContexts()
    {
        if (!m_BDE_USL_Six12ShotContexts)
            return;

        int now = GetGame().GetTime();
        for (int i = m_BDE_USL_Six12ShotContexts.Count() - 1; i >= 0; i--)
        {
            BDE_USL_Six12ShotContext context = m_BDE_USL_Six12ShotContexts.Get(i);
            if (!context || now - context.m_CreatedAt > 10000)
                m_BDE_USL_Six12ShotContexts.Remove(i);
        }
    }

    protected BDE_USL_Six12ShotContext BDE_USL_FindSix12ShotByIdentity(int shotId, Object source, string ammoType)
    {
        if (!m_BDE_USL_Six12ShotContexts)
            return null;

        for (int i = m_BDE_USL_Six12ShotContexts.Count() - 1; i >= 0; i--)
        {
            BDE_USL_Six12ShotContext context = m_BDE_USL_Six12ShotContexts.Get(i);
            if (!context || context.m_ShotId != shotId)
                continue;
            if (source && context.m_Source != source)
                continue;
            if (ammoType != "" && context.m_AmmoType != ammoType)
                continue;
            return context;
        }

        return null;
    }

    protected BDE_USL_Six12ShotContext BDE_USL_FindBestSix12Shot(string ammoType, Object engineSource, vector callbackPosition, vector inSpeed)
    {
        if (!m_BDE_USL_Six12ShotContexts)
            return null;

        BDE_USL_PruneSix12ShotContexts();
        int now = GetGame().GetTime();
        BDE_USL_Six12ShotContext bestContext = null;
        float bestScore = -1000.0;

        for (int i = m_BDE_USL_Six12ShotContexts.Count() - 1; i >= 0; i--)
        {
            BDE_USL_Six12ShotContext context = m_BDE_USL_Six12ShotContexts.Get(i);
            if (!context || context.m_AmmoType != ammoType || context.m_EngineImpactObserved)
                continue;
            if (context.m_FireResultKnown && !context.m_FireResult)
                continue;

            int age = now - context.m_CreatedAt;
            if (age < 0 || age > 10000)
                continue;

            if (engineSource && engineSource != context.m_Source && engineSource != context.m_Host)
            {
                EntityAI sourceEntity = EntityAI.Cast(context.m_Source);
                Man shooter = null;
                if (sourceEntity)
                    shooter = sourceEntity.GetHierarchyRootPlayer();

                if (!shooter || engineSource != shooter)
                    continue;
            }

            vector flatShot = Vector(context.m_ShotDirection[0], 0, context.m_ShotDirection[2]);
            vector flatTravel = callbackPosition - context.m_ProjectilePosition;
            flatTravel[1] = 0;
            vector flatImpactVelocity = Vector(inSpeed[0], 0, inSpeed[2]);

            float routeDot = 1.0;
            float velocityDot = 1.0;
            if (flatShot.Length() > 0.001 && flatTravel.Length() > 0.001)
                routeDot = vector.Dot(flatShot.Normalized(), flatTravel.Normalized());
            if (flatShot.Length() > 0.001 && flatImpactVelocity.Length() > 0.001)
                velocityDot = vector.Dot(flatShot.Normalized(), flatImpactVelocity.Normalized());
            if (routeDot < 0.20)
                continue;

            float score = (routeDot * 2.0) + (velocityDot * 0.5) - (age * 0.00005);
            if (score > bestScore)
            {
                bestScore = score;
                bestContext = context;
            }
        }

        return bestContext;
    }

    void BDE_USL_RegisterSix12Shot(Object source, Object host, string ammoType, vector projectilePosition, vector shotDirection, vector inheritedVelocity, float launchSpeed, int shotId)
    {
        if (!IsServer() || !source || !BDE_USL_IsSix12ProjectileAmmo(ammoType))
            return;

        if (!m_BDE_USL_Six12ShotContexts)
            m_BDE_USL_Six12ShotContexts = new array<ref BDE_USL_Six12ShotContext>;

        BDE_USL_PruneSix12ShotContexts();
        m_BDE_USL_Six12ShotContexts.Insert(new BDE_USL_Six12ShotContext(source, host, ammoType, projectilePosition, shotDirection, inheritedVelocity, launchSpeed, shotId, GetGame().GetTime()));
        Print("[BDE SIX12 TELEMETRY] REGISTER shotId=" + shotId + " ammo=" + ammoType + " source=" + source + " host=" + host + " origin=" + projectilePosition + " direction=" + shotDirection + " inheritedVelocity=" + inheritedVelocity + " launchSpeed=" + launchSpeed);
    }

    void BDE_USL_MarkSix12FireResult(int shotId, Object source, string ammoType, bool fired)
    {
        if (!IsServer())
            return;

        BDE_USL_Six12ShotContext context = BDE_USL_FindSix12ShotByIdentity(shotId, source, ammoType);
        if (!context)
            return;

        context.m_FireResultKnown = true;
        context.m_FireResult = fired;
        Print("[BDE SIX12 TELEMETRY] FIRE_RESULT shotId=" + shotId + " ammo=" + ammoType + " source=" + source + " fired=" + fired);
        if (fired)
            BDE_USL_StartSix12Watchdog(context);
        else
            context.m_WatchActive = false;
    }

    protected void BDE_USL_MarkSix12ImpactObserved(BDE_USL_Six12ShotContext context)
    {
        if (!context)
            return;

        context.m_EngineImpactObserved = true;
        context.m_FallbackQueued = false;
        context.m_WatchActive = false;
    }

    protected void BDE_USL_ObserveSix12Impact(string ammoType, Object engineSource, vector callbackPosition, vector inSpeed, string callbackName)
    {
        if (!IsServer() || !BDE_USL_IsSix12ProjectileAmmo(ammoType))
            return;

        BDE_USL_Six12ShotContext context = BDE_USL_FindBestSix12Shot(ammoType, engineSource, callbackPosition, inSpeed);
        if (context)
        {
            int callbackAge = GetGame().GetTime() - context.m_CreatedAt;
            Print("[BDE SIX12 TELEMETRY] ENGINE_CALLBACK shotId=" + context.m_ShotId + " callback=" + callbackName + " ammo=" + ammoType + " engineSource=" + engineSource + " expectedSource=" + context.m_Source + " matched=true ageMs=" + callbackAge + " predictedImpactAtMs=" + context.m_PredictedImpactAt + " position=" + callbackPosition + " inSpeed=" + inSpeed);
            BDE_USL_MarkSix12ImpactObserved(context);
        }
        else
        {
            Print("[BDE SIX12 TELEMETRY] ENGINE_CALLBACK callback=" + callbackName + " ammo=" + ammoType + " engineSource=" + engineSource + " matched=false position=" + callbackPosition + " inSpeed=" + inSpeed);
        }
    }

    protected bool BDE_USL_Six12WatchdogShouldIgnoreHit(BDE_USL_Six12ShotContext context, Object hitObject)
    {
        if (!context || !hitObject)
            return false;
        if (hitObject == context.m_Source || hitObject == context.m_Host)
            return true;

        EntityAI sourceEntity = EntityAI.Cast(context.m_Source);
        Man shooter = null;
        if (sourceEntity)
            shooter = sourceEntity.GetHierarchyRootPlayer();
        if (shooter && hitObject == shooter)
            return true;

        EntityAI hitEntity = EntityAI.Cast(hitObject);
        if (hitEntity)
        {
            if (context.m_Host && hitEntity.GetHierarchyParent() == context.m_Host)
                return true;
            if (shooter && hitEntity.GetHierarchyRootPlayer() == shooter)
                return true;
        }

        return false;
    }

    protected bool BDE_USL_Six12TraceRay(BDE_USL_Six12ShotContext context, vector startPosition, vector endPosition, out vector hitPosition, out vector hitNormal, out int hitComponent, out Object hitObject)
    {
        hitObject = null;
        hitComponent = -1;
        vector traceDirection = endPosition - startPosition;
        float traceLength = traceDirection.Length();
        if (traceLength <= 0.0001)
            return false;

        traceDirection = traceDirection * (1.0 / traceLength);
        vector traceStart = startPosition;
        set<Object> results = new set<Object>;
        Object ignoreObject = null;
        EntityAI sourceEntity = EntityAI.Cast(context.m_Source);
        if (sourceEntity && sourceEntity.GetHierarchyRootPlayer())
            ignoreObject = sourceEntity.GetHierarchyRootPlayer();

        for (int pass = 0; pass < 8; pass++)
        {
            results.Clear();
            hitObject = null;
            bool hit = DayZPhysics.RaycastRV(traceStart, endPosition, hitPosition, hitNormal, hitComponent, results, null, ignoreObject, false, false, ObjIntersectFire, 0.001, CollisionFlags.NEARESTCONTACT);
            if (!hit)
                return false;
            if (results.Count() > 0)
                hitObject = results[0];
            if (!BDE_USL_Six12WatchdogShouldIgnoreHit(context, hitObject))
                return true;

            traceStart = hitPosition + (traceDirection * 0.03);
            if (vector.Distance(startPosition, traceStart) >= traceLength)
                return false;
        }

        return false;
    }

    protected void BDE_USL_StartSix12Watchdog(BDE_USL_Six12ShotContext context)
    {
        if (!IsServer() || !context || context.m_WatchActive || context.m_EngineImpactObserved)
            return;

        context.m_WatchPosition = context.m_ProjectilePosition;
        context.m_WatchVelocity = (context.m_ShotDirection * context.m_LaunchSpeed) + context.m_InheritedVelocity;
        context.m_WatchLastTickAt = GetGame().GetTime();
        context.m_WatchActive = true;
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_Six12WatchdogTick, 1, false, context.m_ShotId, context.m_Source, context.m_AmmoType);
    }

    protected void BDE_USL_Six12WatchdogTick(int shotId, Object expectedSource, string expectedAmmoType)
    {
        if (!IsServer())
            return;

        BDE_USL_Six12ShotContext context = BDE_USL_FindSix12ShotByIdentity(shotId, expectedSource, expectedAmmoType);
        if (!context || !context.m_WatchActive)
            return;
        if (context.m_EngineImpactObserved || !context.m_FireResultKnown || !context.m_FireResult)
        {
            context.m_WatchActive = false;
            return;
        }

        int now = GetGame().GetTime();
        int ageMs = now - context.m_CreatedAt;
        float ttlSeconds = ConfigGetFloat("CfgAmmo " + context.m_AmmoType + " timeToLive");
        if (ttlSeconds <= 0.0)
            ttlSeconds = 5.0;
        if (ageMs < 0 || ageMs > (int)Math.Ceil(ttlSeconds * 1000.0))
        {
            context.m_WatchActive = false;
            return;
        }

        int elapsedMs = now - context.m_WatchLastTickAt;
        if (elapsedMs <= 0)
        {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_Six12WatchdogTick, BDE_USL_WATCHDOG_TICK_MS, false, shotId, expectedSource, expectedAmmoType);
            return;
        }

        float remaining = elapsedMs * 0.001;
        float airFriction = ConfigGetFloat("CfgAmmo " + context.m_AmmoType + " airFriction");
        vector currentPosition = context.m_WatchPosition;
        vector currentVelocity = context.m_WatchVelocity;

        while (remaining > 0.00001)
        {
            float dt = remaining;
            if (dt > 0.005)
                dt = 0.005;

            float speed = currentVelocity.Length();
            vector acceleration = currentVelocity * (airFriction * speed);
            acceleration[1] = acceleration[1] - 9.81;
            vector nextPosition = currentPosition + (currentVelocity * dt) + (acceleration * (0.5 * dt * dt));
            vector nextVelocity = currentVelocity + (acceleration * dt);
            vector hitPosition;
            vector hitNormal;
            int hitComponent;
            Object hitObject;

            if (BDE_USL_Six12TraceRay(context, currentPosition, nextPosition, hitPosition, hitNormal, hitComponent, hitObject))
            {
                context.m_WatchActive = false;
                context.m_WatchPosition = hitPosition;
                context.m_PredictedImpactAt = now - context.m_CreatedAt;
                context.m_PredictedReason = "ballistic_trace_hit";
                Print("[BDE SIX12 TELEMETRY] PREDICTED_IMPACT shotId=" + context.m_ShotId + " ammo=" + context.m_AmmoType + " timeMs=" + context.m_PredictedImpactAt + " position=" + hitPosition + " normal=" + hitNormal + " component=" + hitComponent + " object=" + hitObject + " graceMs=" + BDE_USL_WATCHDOG_IMPACT_GRACE_MS);
                BDE_USL_QueueSix12Fallback(context, hitPosition, hitNormal, hitComponent, hitObject);
                return;
            }

            currentPosition = nextPosition;
            currentVelocity = nextVelocity;
            remaining = remaining - dt;
        }

        context.m_WatchPosition = currentPosition;
        context.m_WatchVelocity = currentVelocity;
        context.m_WatchLastTickAt = now;
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_Six12WatchdogTick, BDE_USL_WATCHDOG_TICK_MS, false, shotId, expectedSource, expectedAmmoType);
    }

    protected void BDE_USL_QueueSix12Fallback(BDE_USL_Six12ShotContext context, vector impactPosition, vector impactNormal, int hitComponent, Object hitObject)
    {
        if (!IsServer() || !context || context.m_EngineImpactObserved || context.m_FallbackQueued)
            return;

        context.m_FallbackQueued = true;
        Print("[BDE SIX12 TELEMETRY] FALLBACK_QUEUED shotId=" + context.m_ShotId + " reason=no_engine_callback_before_grace predictedReason=" + context.m_PredictedReason + " predictedTimeMs=" + context.m_PredictedImpactAt + " impact=" + impactPosition);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_RunSix12Fallback, BDE_USL_WATCHDOG_IMPACT_GRACE_MS, false, context.m_ShotId, context.m_Source, context.m_AmmoType, impactPosition, impactNormal, hitComponent, hitObject);
    }

    protected void BDE_USL_ApplySix12FallbackHit(BDE_USL_Six12ShotContext context, Object hitObject, int hitComponent, vector hitPosition)
    {
        if (!context || !hitObject)
            return;

        if (BDE_USL_IsProtectedImpact(hitObject, hitPosition, false))
            return;

        EntityAI damageSource = EntityAI.Cast(context.m_Source);
        if (!damageSource)
            damageSource = EntityAI.Cast(context.m_Host);
        if (!damageSource)
            return;

        string componentName = hitObject.GetActionComponentName(hitComponent, "fire");
        vector modelPosition = hitObject.WorldToModel(hitPosition);
        hitObject.ProcessDirectDamage(DamageType.FIRE_ARM, damageSource, componentName, context.m_AmmoType, modelPosition, 1.0, ProcessDirectDamageFlags.ALL_TRANSFER);
    }

    protected void BDE_USL_ExecuteSix12FinalFallback(BDE_USL_Six12ShotContext context, vector impactPosition, int hitComponent, Object hitObject)
    {
        if (!context || context.m_EngineImpactObserved)
            return;

        Print("[BDE SIX12 TELEMETRY] FALLBACK_EXECUTE shotId=" + context.m_ShotId + " ammo=" + context.m_AmmoType + " reason=engine_callback_missing_after_grace predictedTimeMs=" + context.m_PredictedImpactAt + " impact=" + impactPosition + " object=" + hitObject + " component=" + hitComponent);

        int projectileCount = ConfigGetInt("CfgAmmo " + context.m_AmmoType + " projectilesCount");
        if (projectileCount <= 1)
        {
            BDE_USL_ApplySix12FallbackHit(context, hitObject, hitComponent, impactPosition);
            context.m_EngineImpactObserved = true;
            return;
        }

        float dispersion = ConfigGetFloat("CfgAmmo " + context.m_AmmoType + " dispersion");
        float dispersionDegrees = dispersion * 57.2957795;
        float maxDistance = vector.Distance(context.m_ProjectilePosition, impactPosition) + 1.0;
        if (maxDistance < 1.0)
            maxDistance = 1.0;

        vector baseAngles = context.m_ShotDirection.VectorToAngles();
        for (int pelletIndex = 0; pelletIndex < projectileCount; pelletIndex++)
        {
            float fraction = pelletIndex + 1;
            fraction = fraction / projectileCount;
            float radial = dispersionDegrees * (0.30 + (0.70 * fraction));
            float ringRadians = ((pelletIndex * 137.5) + context.m_ShotId) * 0.0174532925;
            vector pelletAngles = baseAngles;
            pelletAngles[0] = pelletAngles[0] + (Math.Cos(ringRadians) * radial);
            pelletAngles[1] = pelletAngles[1] + (Math.Sin(ringRadians) * radial);
            vector pelletDirection = pelletAngles.AnglesToVector();
            pelletDirection.Normalize();

            vector pelletHitPosition;
            vector pelletHitNormal;
            int pelletHitComponent;
            Object pelletHitObject;
            vector pelletEnd = context.m_ProjectilePosition + (pelletDirection * maxDistance);
            if (BDE_USL_Six12TraceRay(context, context.m_ProjectilePosition, pelletEnd, pelletHitPosition, pelletHitNormal, pelletHitComponent, pelletHitObject))
                BDE_USL_ApplySix12FallbackHit(context, pelletHitObject, pelletHitComponent, pelletHitPosition);
        }

        context.m_EngineImpactObserved = true;
    }

    protected void BDE_USL_RunSix12Fallback(int shotId, Object expectedSource, string expectedAmmoType, vector impactPosition, vector impactNormal, int hitComponent, Object hitObject)
    {
        if (!IsServer())
            return;

        BDE_USL_Six12ShotContext context = BDE_USL_FindSix12ShotByIdentity(shotId, expectedSource, expectedAmmoType);
        if (!context)
            return;

        context.m_FallbackQueued = false;
        if (context.m_EngineImpactObserved || !context.m_FireResultKnown || !context.m_FireResult)
            return;

        BDE_USL_ExecuteSix12FinalFallback(context, impactPosition, hitComponent, hitObject);
    }

    protected bool BDE_USL_WatchdogShouldIgnoreHit(BDE_USL_40mmShotContext context, Object hitObject)
    {
        if (!context || !hitObject)
            return false;

        if (hitObject == context.m_Source || hitObject == context.m_FallbackDamageSource)
            return true;

        EntityAI sourceEntity = EntityAI.Cast(context.m_Source);

        if (!sourceEntity)
            return false;

        EntityAI hostEntity = sourceEntity.GetHierarchyParent();

        if (hostEntity && hitObject == hostEntity)
            return true;

        Man shooter = sourceEntity.GetHierarchyRootPlayer();

        if (shooter && hitObject == shooter)
            return true;

        EntityAI hitEntity = EntityAI.Cast(hitObject);

        if (hitEntity)
        {
            if (hostEntity && hitEntity.GetHierarchyParent() == hostEntity)
                return true;

            if (shooter && hitEntity.GetHierarchyRootPlayer() == shooter)
                return true;
        }

        return false;
    }

    protected bool BDE_USL_WatchdogTraceSegment(BDE_USL_40mmShotContext context, vector startPosition, vector endPosition, out vector hitPosition)
    {
        vector traceDirection = endPosition - startPosition;
        float traceLength = traceDirection.Length();

        if (traceLength <= 0.0001)
            return false;

        traceDirection = traceDirection * (1.0 / traceLength);
        vector traceStart = startPosition;
        set<Object> results = new set<Object>;
        Object ignoreObject = null;
        EntityAI sourceEntity = EntityAI.Cast(context.m_Source);

        if (sourceEntity && sourceEntity.GetHierarchyRootPlayer())
            ignoreObject = sourceEntity.GetHierarchyRootPlayer();

        for (int pass = 0; pass < 8; pass++)
        {
            results.Clear();
            Object hitObject = null;
            vector hitNormal;
            int hitComponent = -1;

            bool hit = DayZPhysics.RaycastRV(traceStart, endPosition, hitPosition, hitNormal, hitComponent, results, null, ignoreObject, false, false, ObjIntersectFire, 0.02, CollisionFlags.NEARESTCONTACT);

            if (!hit)
                return false;

            if (results.Count() > 0)
                hitObject = results[0];

            if (!BDE_USL_WatchdogShouldIgnoreHit(context, hitObject))
                return true;

            traceStart = hitPosition + (traceDirection * 0.03);

            if (vector.Distance(startPosition, traceStart) >= traceLength)
                return false;
        }

        return false;
    }

    protected EntityAI BDE_USL_GetTerminalDamageSource(BDE_USL_40mmShotContext context)
    {
        if (!context)
            return null;

        EntityAI source = EntityAI.Cast(context.m_Source);

        if (source)
            return source;

        return EntityAI.Cast(context.m_FallbackDamageSource);
    }

    protected void BDE_USL_MarkTerminalEffectHandled(BDE_USL_40mmShotContext context)
    {
        if (!context)
            return;

        context.m_TerminalEffectHandled = true;
        context.m_TerminalFallbackQueued = false;
        context.m_WatchActive = false;
    }

    protected bool BDE_USL_ExecuteTerminalPayload(BDE_USL_40mmShotContext context, vector impactPosition)
    {
        if (!IsServer() || !context || context.m_TerminalEffectHandled)
            return false;

        if (!context.m_FireResultKnown || !context.m_FireResult)
            return false;

        if (context.m_AmmoType == "Bullet_40mm_Explosive" || context.m_AmmoType == "Bullet_VOG25")
        {
            EntityAI damageSource = BDE_USL_GetTerminalDamageSource(context);

            if (!damageSource)
                return false;

            BDE_USL_MarkTerminalEffectHandled(context);
            if (BDE_USL_IsProtectedImpact(null, impactPosition, true))
                return true;
            DamageSystem.ExplosionDamage(damageSource, null, "Explosion_40mm_Ammo", impactPosition, DamageType.EXPLOSION);
            return true;
        }

        if (context.m_AmmoType == "Bullet_40mm_ChemGas")
        {
            if (BDE_USL_IsProtectedImpact(null, impactPosition, true))
            {
                BDE_USL_MarkTerminalEffectHandled(context);
                return true;
            }
            Object gasArea = GetGame().CreateObject("ContaminatedArea_Local", impactPosition);

            if (!gasArea)
                return false;

            BDE_USL_MarkTerminalEffectHandled(context);
            return true;
        }

        return false;
    }

    protected void BDE_USL_StartTerminalWatchdog(BDE_USL_40mmShotContext context)
    {
        if (!IsServer() || !context || context.m_WatchActive || context.m_TerminalEffectHandled)
            return;

        context.m_WatchPosition = context.m_ProjectilePosition;
        context.m_WatchVelocity = (context.m_ShotDirection * context.m_LaunchSpeed) + context.m_InheritedVelocity;
        context.m_WatchLastTickAt = GetGame().GetTime();
        context.m_WatchActive = true;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_TerminalWatchdogTick, 1, false, context.m_ShotId, context.m_Source, context.m_AmmoType);
    }

    protected void BDE_USL_TerminalWatchdogTick(int shotId, Object expectedSource, string expectedAmmoType)
    {
        if (!IsServer())
            return;

        BDE_USL_40mmShotContext context = BDE_USL_Find40mmShotByIdentity(shotId, expectedSource, expectedAmmoType);

        if (!context || !context.m_WatchActive)
            return;

        if (context.m_TerminalEffectHandled || !context.m_FireResultKnown || !context.m_FireResult)
        {
            context.m_WatchActive = false;
            return;
        }

        int now = GetGame().GetTime();
        int ageMs = now - context.m_CreatedAt;
        float ttlSeconds = ConfigGetFloat("CfgAmmo " + context.m_AmmoType + " timeToLive");

        if (ageMs < 0 || ageMs > (int)Math.Ceil(ttlSeconds * 1000.0))
        {
            context.m_WatchActive = false;
            return;
        }

        int elapsedMs = now - context.m_WatchLastTickAt;

        if (elapsedMs <= 0)
        {
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_TerminalWatchdogTick, BDE_USL_WATCHDOG_TICK_MS, false, shotId, expectedSource, expectedAmmoType);
            return;
        }

        float remaining = elapsedMs * 0.001;
        float airFriction = ConfigGetFloat("CfgAmmo " + context.m_AmmoType + " airFriction");
        vector currentPosition = context.m_WatchPosition;
        vector currentVelocity = context.m_WatchVelocity;

        while (remaining > 0.00001)
        {
            float dt = remaining;

            if (dt > 0.01)
                dt = 0.01;

            float speed = currentVelocity.Length();
            vector acceleration = currentVelocity * (airFriction * speed);
            acceleration[1] = acceleration[1] - 9.81;

            vector nextPosition = currentPosition + (currentVelocity * dt) + (acceleration * (0.5 * dt * dt));
            vector nextVelocity = currentVelocity + (acceleration * dt);
            vector hitPosition;

            if (BDE_USL_WatchdogTraceSegment(context, currentPosition, nextPosition, hitPosition))
            {
                context.m_WatchActive = false;
                context.m_WatchPosition = hitPosition;

                BDE_USL_QueueTerminalFallback(context, hitPosition);
                return;
            }

            currentPosition = nextPosition;
            currentVelocity = nextVelocity;
            remaining = remaining - dt;
        }

        context.m_WatchPosition = currentPosition;
        context.m_WatchVelocity = currentVelocity;
        context.m_WatchLastTickAt = now;

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_TerminalWatchdogTick, BDE_USL_WATCHDOG_TICK_MS, false, shotId, expectedSource, expectedAmmoType);
    }

    protected void BDE_USL_QueueTerminalFallback(BDE_USL_40mmShotContext context, vector impactPosition)
    {
        if (!IsServer() || !context || context.m_TerminalEffectHandled || context.m_TerminalFallbackQueued)
            return;

        context.m_TerminalFallbackQueued = true;
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_RunTerminalFallback, BDE_USL_WATCHDOG_IMPACT_GRACE_MS, false, context.m_ShotId, context.m_Source, context.m_AmmoType, impactPosition);
    }

    protected bool BDE_USL_TryTerminal40mmPhysicalRetry(BDE_USL_40mmShotContext context, vector impactPosition)
    {
        if (!IsServer() || !context || context.m_PhysicalAttempts >= BDE_USL_WATCHDOG_MAX_PHYSICAL_ATTEMPTS || !context.m_Source)
            return false;

        context.m_PhysicalAttempts = context.m_PhysicalAttempts + 1;

        Param6<string, vector, vector, vector, int, vector> retryParams = new Param6<string, vector, vector, vector, int, vector>(context.m_AmmoType, context.m_ProjectilePosition, context.m_ShotDirection, context.m_InheritedVelocity, context.m_ShotId, impactPosition);

        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLaterByName(context.m_Source, "BDE_USL_WatchdogRetryPhysicalShotDispatch", 0, false, retryParams);
        Print("[BDE USL WATCHDOG] 40mm physical attempt " + context.m_PhysicalAttempts + "/" + BDE_USL_WATCHDOG_MAX_PHYSICAL_ATTEMPTS + " dispatched shotId=" + context.m_ShotId + " ammo=" + context.m_AmmoType);
        return true;
    }

    void BDE_USL_Report40mmPhysicalRetry(int shotId, Object source, string ammoType, bool fired, vector impactPosition)
    {
        if (!IsServer())
            return;

        BDE_USL_40mmShotContext context = BDE_USL_Find40mmShotByIdentity(shotId, source, ammoType);
        if (!context)
            return;

        Print("[BDE USL WATCHDOG] 40mm physical attempt " + context.m_PhysicalAttempts + "/" + BDE_USL_WATCHDOG_MAX_PHYSICAL_ATTEMPTS + " shotId=" + shotId + " ammo=" + ammoType + " fired=" + fired);

        if (fired)
        {
            context.m_CreatedAt = GetGame().GetTime();
            context.m_WatchPosition = context.m_ProjectilePosition;
            context.m_WatchVelocity = (context.m_ShotDirection * context.m_LaunchSpeed) + context.m_InheritedVelocity;
            context.m_WatchLastTickAt = context.m_CreatedAt;
            context.m_WatchActive = true;
            context.m_TerminalFallbackQueued = false;
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(BDE_USL_TerminalWatchdogTick, 1, false, context.m_ShotId, context.m_Source, context.m_AmmoType);
            return;
        }

        if (context.m_PhysicalAttempts < BDE_USL_WATCHDOG_MAX_PHYSICAL_ATTEMPTS && BDE_USL_TryTerminal40mmPhysicalRetry(context, impactPosition))
            return;

        if (context.m_Source)
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLaterByName(context.m_Source, "BDE_USL_WatchdogRetryCleanup", 0, false, new Param1<string>(context.m_AmmoType));

        Print("[BDE USL WATCHDOG] 40mm five physical attempts failed; using simulated terminal fallback shotId=" + context.m_ShotId + " ammo=" + context.m_AmmoType);
        BDE_USL_ExecuteTerminalPayload(context, impactPosition);
    }

    protected void BDE_USL_RunTerminalFallback(int shotId, Object expectedSource, string expectedAmmoType, vector impactPosition)
    {
        if (!IsServer())
            return;

        BDE_USL_40mmShotContext context = BDE_USL_Find40mmShotByIdentity(shotId, expectedSource, expectedAmmoType);
        if (!context)
            return;

        context.m_TerminalFallbackQueued = false;
        if (context.m_TerminalEffectHandled || !context.m_FireResultKnown || !context.m_FireResult)
            return;

        if (context.m_PhysicalAttempts < BDE_USL_WATCHDOG_MAX_PHYSICAL_ATTEMPTS && BDE_USL_TryTerminal40mmPhysicalRetry(context, impactPosition))
            return;

        if (context.m_Source)
            GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLaterByName(context.m_Source, "BDE_USL_WatchdogRetryCleanup", 0, false, new Param1<string>(context.m_AmmoType));

        Print("[BDE USL WATCHDOG] 40mm five physical attempts failed; using simulated terminal fallback shotId=" + context.m_ShotId + " ammo=" + context.m_AmmoType);
        BDE_USL_ExecuteTerminalPayload(context, impactPosition);
    }

    protected void BDE_USL_HandleProjectileStopped(ProjectileStoppedInfo info)
    {
        if (!IsServer() || !info)
            return;

        string ammoType = info.GetAmmoType();

        if (BDE_USL_IsSix12ProjectileAmmo(ammoType))
            BDE_USL_ObserveSix12Impact(ammoType, info.GetSource(), info.GetPos(), info.GetInVelocity(), "OnProjectileStopped");

        if (!BDE_USL_IsTerminalPayload40mmAmmo(ammoType))
            return;

        BDE_USL_40mmShotContext context = BDE_USL_FindBest40mmShot(ammoType, info.GetSource(), info.GetPos(), info.GetInVelocity());

        if (context)
            BDE_USL_QueueTerminalFallback(context, info.GetPos());
    }

    override void OnProjectileStopped(ProjectileStoppedInfo info)
    {
        BDE_USL_HandleProjectileStopped(info);
        super.OnProjectileStopped(info);
    }

    override void OnProjectileStoppedInTerrain(TerrainCollisionInfo info)
    {
        if (IsServer() && info && BDE_USL_IsSix12ProjectileAmmo(info.GetAmmoType()))
            BDE_USL_ObserveSix12Impact(info.GetAmmoType(), info.GetSource(), info.GetPos(), info.GetInVelocity(), "OnProjectileStoppedInTerrain");
        else
            BDE_USL_HandleProjectileStopped(info);
        super.OnProjectileStoppedInTerrain(info);
    }

    override void OnProjectileStoppedInObject(ObjectCollisionInfo info)
    {
        if (IsServer() && info && BDE_USL_IsSix12ProjectileAmmo(info.GetAmmoType()))
            BDE_USL_ObserveSix12Impact(info.GetAmmoType(), info.GetSource(), info.GetPos(), info.GetInVelocity(), "OnProjectileStoppedInObject");
        else
            BDE_USL_HandleProjectileStopped(info);
        super.OnProjectileStoppedInObject(info);
    }

    // The terminal payload has already been handled. Preserve vanilla server hit
    // noise without forwarding a null source to other mods' explosion handlers.
    protected void BDE_USL_HandledTerminalImpactNoise(Object directHit, int componentIndex, vector pos, vector inSpeed, string ammoType)
    {
        if (!IsServer())
            return;

        m_NoiseParams.LoadFromPath("cfgAmmo " + ammoType + " NoiseHit");

        float surfaceCoef = SurfaceGetNoiseMultiplier(directHit, pos, componentIndex);
        float initSpeed = ConfigGetFloat("cfgAmmo " + ammoType + " initSpeed");
        float coefAdjusted = 1;

        if (initSpeed > 0)
            coefAdjusted = surfaceCoef * inSpeed.Length() / initSpeed;

        if (coefAdjusted == 0)
            coefAdjusted = 1;

        GetNoiseSystem().AddNoiseTarget(pos, 10, m_NoiseParams, coefAdjusted);
    }
    override void FirearmEffects(Object source, Object directHit, int componentIndex, string surface, vector pos, vector surfNormal, vector exitPos, vector inSpeed, vector outSpeed, bool isWater, bool deflected, string ammoType)
    {
        if (IsServer() && BDE_USL_IsSix12ProjectileAmmo(ammoType))
            BDE_USL_ObserveSix12Impact(ammoType, source, pos, inSpeed, "FirearmEffects");

        int recoveredShotId = -1;
        bool serverSourceNotExplosive = IsServer() && source && !source.ShootsExplosiveAmmo();

        if ((!source || serverSourceNotExplosive) && BDE_USL_IsTerminalPayload40mmAmmo(ammoType))
        {
            Object recoveredSource;

            if (IsServer())
                recoveredSource = BDE_USL_ResolveServer40mmFireSource(ammoType, pos, inSpeed, recoveredShotId);
            else
                recoveredSource = BDE_USL_ResolveClient40mmFireSource(ammoType, pos, inSpeed, recoveredShotId);

            if (recoveredSource)
                source = recoveredSource;
        }

        if (IsServer() && BDE_USL_IsTerminalPayload40mmAmmo(ammoType) && !deflected && outSpeed == vector.Zero)
        {
            BDE_USL_40mmShotContext terminalContext = null;

            if (recoveredShotId >= 0)
                terminalContext = BDE_USL_Find40mmShotByIdentity(recoveredShotId, source, ammoType);

            if (!terminalContext)
                terminalContext = BDE_USL_FindBest40mmShot(ammoType, source, pos, inSpeed);

            if (terminalContext)
            {
                terminalContext.m_WatchActive = false;
                bool payloadHandled = terminalContext.m_TerminalEffectHandled;

                if (!payloadHandled)
                    payloadHandled = BDE_USL_ExecuteTerminalPayload(terminalContext, pos);

                if (payloadHandled)
                {
                    BDE_USL_HandledTerminalImpactNoise(directHit, componentIndex, pos, inSpeed, ammoType);
                    return;
                }
            }
        }

        if (IsServer() && ammoType == "Bullet_VOG25" && source && source.IsKindOf("BDE_GP25") && !deflected && outSpeed == vector.Zero)
        {
            EntityAI handheldGP25 = EntityAI.Cast(source);

            if (handheldGP25)
            {
                if (!BDE_USL_IsProtectedImpact(null, pos, true))
                    DamageSystem.ExplosionDamage(handheldGP25, null, "Explosion_40mm_Ammo", pos, DamageType.EXPLOSION);
                BDE_USL_HandledTerminalImpactNoise(directHit, componentIndex, pos, inSpeed, ammoType);
                return;
            }
        }

        super.FirearmEffects(source, directHit, componentIndex, surface, pos, surfNormal, exitPos, inSpeed, outSpeed, isWater, deflected, ammoType);
    }
}
